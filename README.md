Plotty :: Library for text terminal plotter
===========================================

This is the basic building block for a text based plotter inspired by
mtr (My Traceroute).

      Some text   X [                .....   ] Number
              \    \                      \         `--- activity counter
               \    \                      `------------ activity
                \    `---------------------------------- liveness spinner
                 `-------------------------------------- label

The activity `.....` are dots being inserted at the far right side `]`
bracket, moved one step left for each poll.  No activity in a poll
interval inserts a white space.

See it in action in the [mcjoin](https://github.com/troglobit/mcjoin)
project.


Design Iterations
-----------------

While working on this, before landing on the resulting implementation, I
was playing around with several design ideas for the look and feel.  The
below are just some of the variants.

```
°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸
°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°
°º¤ø,¸,ø¤°º¤ø,¸,ø¤°º¤ø,¸,ø¤°º¤ø,¸,ø¤°º¤ø,¸,ø¤°º¤ø,¸,ø¤°º¤ø,¸,ø¤°º¤ø,¸,ø¤

_.~"~._.~"~._.~"~._.~"~._.~"~._.~"~._.~"~._.~"~._.~"~._.~"~._.~"~._.~"~.
_.~"~._.~"~._.~"~._.~"~.
_.~"~.

----------------o--O-8--8ooo------------


-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-__.-~"~._.~'~

[___________________________________________________________________________]

[---------------------------------------------------------------------------]


[      ...       //O\\              ......                                  ]

[:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]
 .....:..:..:..::.....':':


[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]

[......-=o=-................................................................]

[-------=o=-----------------------------------------------------------------]

[======-o0o-================================================================]

```
