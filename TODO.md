### Big TODO's
- Prepare for first release
  - Add support for compiling from .pro [Added in branch `static_build`]
  - Check minimal qt version (ex. 5.5, or 5.2)
  - Add qca as vendor subproject [Added in branch `static_build`]
    - Migrate to package managers [`conan, hunter, inqlude`]
  
- README
  - Write requirements and build instructions
  - Screenshots


### Current TODO's
- Tab Plugin for content encryption (Show dialog when tab opens)

- Logging
  - Add logging to already written code for debug/bug hunting.

- Fix 2 bugs:
  - Windows blinks multiple times on start
    - Multiple (10-12) random saves after app starts (Maybe it's just auto save after edit ?)
  - Don't work correctly with dock until hidden to tray and shown back

### Low priority TODO's
- Logging
  - qDebug's stream syntax
  - Load logging settings from storage with silent flag

- Logs widget [WIP in branch `logs_widget`]
  - Archiving old logs (store unzipped 2-3 files, rest is in logs.zip)
  - Send logs with button (dunno, host an app for it ?)
  - Check `Q_FUNC_INFO` on other compilers/platforms

- Double-Shift or some other shortcut to quickly go to any tab | switch options

- Encryption of storage with local password
  - Remember me, for time set by user
  
- Welcome screen with quick links to groups/last edited tabs/settings

- Import/Export through menu item
  
- Write docs in code

- Restore and Diff for Backup [Move to sync ?]

- View-only mode for LinkGroup

- Add markdown syntax highlighting and toolbar
  - Custom markdown render to QLabel, etc as module (push to GitHub as separate rep)

- Themes [Light, Dark] as default, and custom (JSON)


#### Other 
##### Needs further checking
- network/NCrypt:decrypt - Validation error prints only to console and message decryption isn't stopped


##### Maybe
- Rewrite to Model-View, to cleanup code and use less code
- Move all "secure" variables from storage to separate file or leave there but encrypted like docs (for ex. to SSecure)
- Move login/register logic to SSecure
- Sync:
  - TOTP [repo 1](https://github.com/RavuAlHemio/cpptotp), [repo 2](https://github.com/andreagrandi/QGoogleAuth)
  - Docs sharing - (one time, continuous, two way, exchange keys with RSA)
