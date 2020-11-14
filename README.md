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
