#include <array>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

#define APP "poe-ease"

inline constexpr char EndL = '\n';

namespace app {
    using Size = std::size_t;
    template < typename Type, Size size > using Flat = std::array< Type, size >;
    using Text = std::string;
    using View = std::string_view;
    using Path = std::filesystem::path;

    using namespace std::string_view_literals;

    enum class Case : std::int8_t {
        Out = 0, In_Norm, In_Less
    };

    struct State {
        Size currLine{ 0 };
        Text currErrt{ "" };
        Case currCase{ Case::Out };
    };

    enum class Rule : std::int8_t {
        Not = 0, Hide_Show, Norm, Less, Ends, Size_,
        Error = -1
    };
    constexpr Size rule_size( ) { return static_cast< Size >( Rule::Size_ ); }

    Rule parse_rule( View line ) {
        if ( line.empty( ) ) throw std::runtime_error{ APP ": empty lines are not allowed in input file" };
        auto checkFirst = line.substr( 1, 1 );
        if ( line[0] != '#' or checkFirst == " "sv or checkFirst == "#"sv ) return Rule::Not;

        static constexpr Flat< View, rule_size( ) > rules{{
            ""sv, "#HIDESHOW"sv, "#NORM:", "#LESS:", "#ENDS."
        }};

        for ( Size i = 1u; i < rules.size( ); ++i ) {
            if ( rules[i] == line ) return static_cast< Rule >( i );
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

    Text line, textNorm, textLess;
    line.reserve( 1u << 12u ); // 4096?
    Size inSize = std::filesystem::file_size( inputFilename );
    if ( inSize > ( 1u << 20u ) ) throw std::runtime_error{ APP ": input file exceeds 1MiB, too large maybe wrong file?" };
    // input file size technically would always be bigger, so only one allocation needed
    textNorm.reserve( inSize );
    textLess.reserve( inSize );

    State state;
    while ( std::getline( in, line ) ) {
        if ( not state.currErrt.empty( ) ) {
            std::cerr << APP << ": line " << state.currLine << ", error: " << state.currErrt << EndL;
            throw std::runtime_error{ state.currErrt };
        }
        ++state.currLine;
        Rule rule = parse_rule( line );
        auto process_default = [&line,&textNorm,&textLess]( State const &currState ) {
            auto state = currState.currCase;
            bool writeNorm = state == Case::Out or state == Case::In_Norm;
            bool writeLess = state == Case::Out or state == Case::In_Less;
            if ( writeNorm ) textNorm += line + EndL;
            if ( writeLess ) textLess += line + EndL;
        };
        auto process_hideshow = [&textNorm,&textLess]( State &state ) {
            if ( state.currCase != Case::Out ) state.currErrt = APP ": #HIDESHOW rule required to be outside #NORM or #LESS case";
            textNorm += "Hide\n";
            textLess += "Show\n";
        };
        switch ( rule ) {
            case Rule::Not: process_default( state ); continue;
            case Rule::Hide_Show: process_hideshow( state ); continue;
            case Rule::Norm: state.currCase = Case::In_Norm; continue;
            case Rule::Less: state.currCase = Case::In_Less; continue;
            case Rule::Ends: state.currCase = Case::Out; continue;
            default: break;
        }
        // NOTE: only rule errors should reach here
        auto ruleNum = static_cast< int >( rule );
        assert( ruleNum < 0 and "assert: logic error - expected only rule errors" );
        std::cerr << APP << ": rule warning " << ruleNum << " line " << state.currLine << EndL;
        std::cerr << "\t" << line.substr( 0, 256 ) << EndL;
    }

    if ( state.currCase != Case::Out ) std::cerr << APP ": warning #NORM or #LESS case are not closed with #ENDS" << EndL;

    Path normFilename{ "campaign.filter" }, lessFilename{ "campaign.ruthlessfilter" };

    using OutFile = std::ofstream;
    OutFile outNorm{ normFilename, std::ios::binary }, outLess{ lessFilename, std::ios::binary };

    if ( not outNorm or not outLess ) throw std::runtime_error{ APP ": Could not create or overwrite out files" };

    outNorm << textNorm;
    outLess << textLess;

} catch ( std::exception const &e ) {
    std::cerr << "std::exception: " << e.what( ) << EndL;
} catch ( ... ) {
    std::cerr << "... exception" << EndL;
}
