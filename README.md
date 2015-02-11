# pidgin-openfetion

a clone of the pidgin plugin of openfetion

project home: https://code.google.com/p/ofetion/

Thanks to happyaron.

## Update

The old version of pidgin-openfetion (including openfetion, cli-openfetion, etc.) doesn't work any more because the official fetion server update the protocol and openfetion will only get a "your fetion client is out of date" when you try to login. And the pidgin (or the other version of openfetion) will CRASHED!

This repo update the login protocol for a little to fix the problem. I follow SmartFetion client, which is truely an old version but is still available at this time.

## Build & Install

1. Clone this repo.
2. Make a new dir `pidgin-openfetion/build`
3. cmake .. && make
4. move `libopenfetion.so` to `~/.purple/plgins`
5. try to login, prey, it will work

## Disclaimer

There is no guarantee for the modification will actually work file. But for me, it does.
