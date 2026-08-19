#include <array>
#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

#define APP "poe-ease"

inline constexpr char EndL = '\n';

namespace app {
    using Size = std::size_t;
    using Int0 = std::int8_t;
    template< typename Type > using Out = Type &;
    template< typename Type > using Ref = Type const &;
    template < typename Type, Size size > using Flat = std::array< Type, size >;
    using Text = std::string;
    using View = std::string_view;
    using Path = std::filesystem::path;

    using namespace std::string_view_literals;

    enum class Case : Int0 {
        Out = 0, In_Norm, In_Less
    };

    enum class Rank : Int0 {
        None, Depth1, Depth2, Depth3
    };

    struct State {
        Size currLine{ 0 };
        Text currErrt{ "" };
        Case currCase{ Case::Out };
        Rank currRank{ Rank::None };
        View currText{ ""sv };
        Size currDep1{ 0 };
        Size currDep2{ 0 };
        Size currDep3{ 0 };
    };

    struct TextState {
        Text norm;
        Text less;
        Text normContents{ "# CONTENTS\n"sv };
        Text lessContents{ "# CONTENTS\n"sv };
    };

    enum class Rule : std::int8_t {
        Not = 0, Part, Hide_Show, Norm, Less, Ends, Size_,
        Error = -1
    };
    constexpr Size rule_size( ) { return static_cast< Size >( Rule::Size_ ); }

    Rule parse_rule( View line ) {
        if ( line.empty( ) ) throw std::runtime_error{ APP ": empty lines are not allowed in input file" };
        auto checkFirst = line.substr( 1, 1 );
        if ( line[0] != '#' or checkFirst == " "sv or checkFirst == "#"sv ) return Rule::Not;

        static constexpr Flat< std::pair< View, Rule >, 5 > rules{{
            { "#PART:*"sv, Rule::Part },
            { "#HIDESHOW$"sv, Rule::Hide_Show },
            { "#NORM:$"sv, Rule::Norm },
            { "#LESS:$"sv, Rule::Less },
            { "#ENDS.$"sv, Rule::Ends }
        }};

        for ( auto const [view,rule] : rules ) {
            char last = view.back( );
            View checkLine{ ""sv }, checkRule{ view.substr( 0, view.size( ) - 1 ) };
            switch ( last ) {
                case '*': checkLine = line.substr( 0, checkRule.size( ) ); break;
                case '$': checkLine = line; break;
                default: assert( false and APP ": logic error in parse_rule, rule does not change with `*` or `$`" ); return Rule::Error;
            }
            if ( checkRule == checkLine ) return rule;
        }

        return Rule::Error;
    }
}

int main( [[maybe_unused]] int argc, [[maybe_unused]] char *argv[] ) try {
    using namespace app;
    // TODO: take argument for input filename,
    // \ and output into normal and ruthless filter under the same name
    Path inputFilename{ "campaign.easefilter" };

    using InFile = std::ifstream;
    InFile in{ inputFilename, std::ios::binary };

    if ( not in ) throw std::runtime_error{ APP ": Could not open input file" };

    Size inSize = std::filesystem::file_size( inputFilename );
    if ( inSize > ( 1u << 20u ) ) throw std::runtime_error{ APP ": input file exceeds 1MiB, too large maybe wrong file?" };

    Text line;
    line.reserve( 1u << 12u ); // 4096?
    TextState text;
    // NOTE: avoid additional allocations
    text.norm.reserve( inSize << 1u );
    text.less.reserve( inSize << 1u );

    State state;
    while ( std::getline( in, line ) ) {
        if ( not state.currErrt.empty( ) ) {
            std::cerr << APP << ": line " << state.currLine << ", error: " << state.currErrt << EndL;
            throw std::runtime_error{ state.currErrt };
        }
        ++state.currLine;
        auto process_default = [&line,&text]( Ref< State > state ) {
            Case c = state.currCase;
            bool writeNorm = c == Case::Out or c == Case::In_Norm;
            bool writeLess = c == Case::Out or c == Case::In_Less;
            if ( writeNorm ) text.norm += line + EndL;
            if ( writeLess ) text.less += line + EndL;
        };
        auto process_text = [&line,&text]( Out< State > state ) {
            // NOTE: currently parts depth numbers are shared between `NORMal`
            // \ and `ruthLESS` mode, so it would mean there can be missing
            // \ of some numbers in singular filter contents (intentional)
            Size from = 5;
            assert( line[from] == ':' and "TODO" );
            Size count{ 0 };
            while ( line[++from] == '-' ) ++count;
            switch ( count ) {
                case 1: ++state.currDep1; state.currDep2 = 0; state.currDep3 = 0; break;
                case 3: ++state.currDep2; state.currDep3 = 0; break;
                case 5: ++state.currDep3; break;
                default: state.currErrt = APP ": #TEXT rule invalid count of `-` characters"; return;
            }
            Text title, tail{ line.substr( 6 ) };

            using namespace std::string_literals;
            if ( state.currDep3 ) {
                Text parts = std::format( "{}.{}.{}", state.currDep1, state.currDep2, state.currDep3 );
                title += std::format( "###   {:<8}{}", parts, tail );
            } else if ( state.currDep2 ) {
                Text parts = std::format( "{}.{}", state.currDep1, state.currDep2 );
                title += std::format( "##    {:<8}{}", parts, tail );
            } else {
                // NOTE: state `currDep1` should always be at least one at this point
                assert( state.currDep1 and APP ": assert cannot be zero here" );
                Text parts = std::format( "{}", state.currDep1 );
                title += std::format( "#     {:<8}{}", parts, tail );
            }
            if ( state.currCase == Case::Out or state.currCase == Case::In_Norm ) {
                text.norm += title + EndL;
                text.normContents += title + EndL;
            }
            if ( state.currCase == Case::Out or state.currCase == Case::In_Less ) {
                text.less += title + EndL;
                text.lessContents += title + EndL;
            }
        };
        auto process_hideshow = [&text]( Out< State > state ) {
            if ( state.currCase != Case::Out ) state.currErrt = APP ": #HIDESHOW rule required to be outside #NORM or #LESS case";
            text.norm += "Hide\n";
            text.less += "Show\n";
        };
        Rule rule = parse_rule( line );
        switch ( rule ) {
            case Rule::Not: process_default( state ); continue;
            case Rule::Part: process_text( state ); continue;
            case Rule::Hide_Show: process_hideshow( state ); continue;
            case Rule::Norm: state.currCase = Case::In_Norm; continue;
            case Rule::Less: state.currCase = Case::In_Less; continue;
            case Rule::Ends: state.currCase = Case::Out; continue;
            default: break;
        }
        // NOTE: only rule errors should reach here
        auto ruleNum = static_cast< int >( rule );
        assert( ruleNum < 0 and APP ": assert logic error - expected only rule errors" );
        std::cerr << APP << ": rule warning " << ruleNum << " line " << state.currLine << EndL;
        std::cerr << "\t" << line.substr( 0, 256 ) << EndL;
    }

    if ( state.currCase != Case::Out ) std::cerr << APP ": warning #NORM or #LESS case are not closed with #ENDS" << EndL;

    Path normFilename{ "campaign.filter" }, lessFilename{ "campaign.ruthlessfilter" };

    using OutFile = std::ofstream;
    OutFile outNorm{ normFilename, std::ios::binary }, outLess{ lessFilename, std::ios::binary };

    if ( not outNorm or not outLess ) throw std::runtime_error{ APP ": Could not create or overwrite out files" };

    outNorm << text.normContents << "# END OF CONTENTS\n" << text.norm;
    outLess << text.lessContents << "# END OF CONTENTS\n" << text.less;

    outNorm.close( );
    outLess.close( );

    if ( outNorm.fail() or outLess.fail() ) throw std::runtime_error{ APP ": Failed writing data to out files" };

    return EXIT_SUCCESS;
} catch ( app::Ref< std::exception > e ) {
    std::cerr << "std::exception: " << e.what( ) << EndL;
    return EXIT_FAILURE;
} catch ( ... ) {
    std::cerr << "... exception" << EndL;
    return EXIT_FAILURE;
}
