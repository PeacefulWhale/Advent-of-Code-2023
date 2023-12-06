# Day One

Whoops, it's already "Day 6" in the AOC calendar... I can probably catch up easily enough though.

## Part One

Part one is simple enough. Loop through and grab the first and last numbers and add them to the sum.

## Part Two

This one is also simple enough. It feels like a regex problem, so I'll treat it like one I guess.

Weird that numbers like "sixteen" are also included but aren't valid...

Oh, and some numbers "overlap" (for example: `eightwo` or `oneight`). This isn't terribly difficult to handle with regex.

I could probably figure out a way of doing it with just a single regex instead of pushing numbers into a dequeue, but I'm rather lazy.
