# <div align="center"> SSSimpler </div>

SSSimpler is a UCI chess engine with NNUE.
## Features
Alpha-Beta search with a bunch of tweaks
## Evaluation
Neural net, architecture is (768x8hm->1024)x2-pw->(16-dual->32-crelu->1)x(8x8).
## Building
Just run `make`
## Strength
Yet to be tested
## License
The code is licensed under the GPLv3 license. Full text can be found in LICENSE in the project root.
## Credit
[Jonathan Hallström](https://github.com/JonathanHallstrom), author of [Pawnocchio](https://github.com/JonathanHallstrom/pawnocchio), for a ton of helping throughout the development, SSSimpler would be much much weaker without him \
[Rektbench](https://rektdie.pythonanywhere.com) gang for helping and providing hardware for testing \
[Bullet](https://github.com/jw1912/bullet/blob/main/docs/0-contents.md) NNUE trainer for training all nets \
[Alpha-Beta](https://discord.gg/t3aX6XkPaV) Discord server for explaining some concepts
