# Day Four

## Part One

I need to count up the total number of winning numbers? I bet part two will add a twist to this but I'll just do this the lazy "keep track of the numbers" way.

## Part Two

As always, the elves are incapable of reading through instructions fully...

When I first read part two, I thought I'd have to go to the card number that matched, but in reality I just have to add that many more copies to the next X cards... so I only need to keep track of the number of matching numbers.

I just had to slightly modify my code to make it work for part 2 in the end.

I used a cache because that (should) make it run a bit faster. I'm too lazy to figure out the "non-recursion" problem. This feels like it was meant to trap people into doing an ineffective recursion system (anyone want to calculate fibonacci numbers with me?), but I hope I avoided that with the cache.
