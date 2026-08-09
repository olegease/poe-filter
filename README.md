# POE-FILTER
> handmade filter for Path of Exile base game and ruthless mode using Heroes of Might and Magic III sounds for item drops

> Disclaimer: All audio assets are the property of their respective copyright owners. This is a free, non-commercial fan project

Last Updated on 3.25 Settlers League

Could potentially misrepresent valuable items or show too much, so use with care!

## Usage
> alpha version, no releases

- copy: `homm3snd/` `imported/` folders with `items.filter` andor `items.ruthlessfilter` into `Path of Exile` filter folder (check game client open folder functionality for correct path)

## Notes
> `TODO`

filter chopped into eight parts:

- continue: basic styles which always contain continue rules for next parts, except
  - quest items
  - starting character class gems at first area only (to play starting sound track)
  - gold
- currency: crafting materials and other orbs
- seasonal: league-related content
- specific: link-related, fractured, influenced and corrupted items
- specials: flasks, gems, maps, divination cards...
- identify: identified items with exotic mods (almost nothing yet, `TODO`)
- rarities: from normal - to unique items that does not belong to previous part (most hide rules are here)
- mistaken: if reach here then error happened

### Ruthless
> only difference between base and ruthless filter is that fonts with inclusion size range `18-30` are hidden in base filter

### Gold

- to look good border and background are fully transparent
- larger piles with bigger font and more yellowish
