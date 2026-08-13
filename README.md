# `POE-FILTER`
> handmade filter for Path of Exile base game and ruthless mode using Heroes of Might and Magic III sounds for item drops

> Disclaimer: All audio assets are the property of their respective copyright owners. This is a free, noncommercial fan project

Last Updated on 3.25 Settlers League

## NO LONGER SUPPORTED
> use as starting point example

Could potentially misrepresent valuable items or show too much, so use with care!

## Usage
> alpha version, no releases

- copy: `homm3snd/` `imported/` folders with `items.filter` andor `items.ruthlessfilter` into `Path of Exile` filter folder (check game client open folder functionality for correct path)

## Official Forum Item Filter Related Announcements

- [`Curse of the Allflame`](https://www.pathofexile.com/forum/view-thread/3986972): _3.29_
- [`Mirage`](https://www.pathofexile.com/forum/view-thread/3914212): _3.28_
- [`Keepers of the Flame`](https://www.pathofexile.com/forum/view-thread/3870283): _3.27_
- [`Secrets of the Atlas`](https://www.pathofexile.com/forum/view-thread/3788869): _3.26_
- [`Settlers of Kalguur`](https://www.pathofexile.com/forum/view-thread/3532553): _3.25_
- [`Necropolis`](https://www.pathofexile.com/forum/view-thread/3497460): _3.24_
- [`Affliction`](https://www.pathofexile.com/forum/view-thread/3452297): _3.23_
- [`Trial of the Ancestors`](https://www.pathofexile.com/forum/view-thread/3410483): _3.22_
- [`Crucible`](https://www.pathofexile.com/forum/view-thread/3362077): _3.21_
- [`The Forbidden Sanctum`](https://www.pathofexile.com/forum/view-thread/3324656): _3.20_
- [`Lake of Kalandra`](https://www.pathofexile.com/forum/view-thread/3294085): _3.19_
- [`Sentinel`](https://www.pathofexile.com/forum/view-thread/3265282): _3.18_
- [`Siege of the Atlas`](https://www.pathofexile.com/forum/view-thread/3230194): _3.17_
- [`Scourge`](https://www.pathofexile.com/forum/view-thread/3187476): _3.16_
- [`Expedition`](https://www.pathofexile.com/forum/view-thread/3147480): _3.15_
- [`Ultimatum`](https://www.pathofexile.com/forum/view-thread/3079980): _3.14_
- [`Echoes of the Atlas`](https://www.pathofexile.com/forum/view-thread/3009221): _3.13 Ritual_
- [`Heist`](https://www.pathofexile.com/forum/view-thread/2935826): _3.12_
- [`Harvest`](https://www.pathofexile.com/forum/view-thread/2873743): _3.11_
- [`Delirium`](https://www.pathofexile.com/forum/view-thread/2784312): _3.10_
- [`Conquerors of the Atlas`](https://www.pathofexile.com/forum/view-thread/2687401): _3.9_
- [`Blight`](https://www.pathofexile.com/forum/view-thread/2627576): _3.8_
- [`Legion`](https://www.pathofexile.com/forum/view-thread/2513458): _3.7_
- [`Synthesis`](https://www.pathofexile.com/forum/view-thread/2333649): _3.6_
- [`Betrayal`](https://www.pathofexile.com/forum/view-thread/2255461): _3.5_
- [`Delve`](https://www.pathofexile.com/forum/view-thread/2201188): _3.4_
- [`Incursion`](https://www.pathofexile.com/forum/view-thread/2150238): _3.3_
- [`Bestiary`](https://www.pathofexile.com/forum/view-thread/2093501): _3.2_
- [`War for the Atlas`](https://www.pathofexile.com/forum/view-thread/2036673): _3.1 Abyss_
- [`The Fall of Oriath `](https://www.pathofexile.com/forum/view-thread/1930848): _3.0 Harbinger_
- [`Legacy`](https://www.pathofexile.com/forum/view-thread/1840246): _2.6_
- [`Breach`](https://www.pathofexile.com/forum/view-thread/1774440): _2.5_
- [`Atlas of Worlds`](https://www.pathofexile.com/forum/view-thread/1716826): _2.4_
- [`Prophecy`](https://www.pathofexile.com/forum/view-thread/1667538): _2.3_
- [`Ascendancy`](https://www.pathofexile.com/forum/view-thread/1595993): _2.2_
- [`The Awakening`](https://www.pathofexile.com/forum/view-thread/1235695): _2.0_

## Notes
> `TODO`

filter chopped into eight parts:

- continue: basic styles which always contain continue rules for next parts, except
  - quest items
  - starting character class gems at first area only (to play starting soundtrack)
  - gold
- currency: crafting materials and other orbs
- seasonal: league-related content
- specific: link-related, fractured, influenced and corrupted items
- specials: flasks, gems, maps, divination cards and other
- identify: identified items with exotic mods (almost nothing yet, `TODO`)
- rarities: from normal - to unique items that does not belong to previous part (most hide rules are here)
- mistaken: if reach here then error happened (and removed items also?)

### Ruthless
> only difference between base and ruthless filter is that fonts with inclusion size range `18-30` are hidden in base filter

### Gold

- to look good border and background are fully transparent
- larger piles with bigger font and more yellowish
