## SOURCE
> source code directory

- tool name `ease-filter`
- filter tool extension `.easefilter`
- rules:
  - `#HIDESHOW`: `Hide` in normal mode `Show` in ruthless
  - `#NORM:`: conditional applied if not a ruthless mode
  - `#LESS:`: conditional that applied for ruthless mode (TODO: only if `-L` or `--ruthless` command argument passed)
  - `#ELSE:`: else conditional
  - `#ENDS.`: end conditional

### Usage

Generates both filter files for ruthless and normal game, `[.easefilter]` means that extension could be omitted

```
$ ease-filter filename-with-extension[.easefilter]
```
