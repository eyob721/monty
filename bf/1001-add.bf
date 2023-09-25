# First get the ascii value of 0 which is 48 on mem1 use a counter 5 on mem0
+++++
[
    > +++++ +++++
<-
]           # After the loop mem1 is 50
> --        # Go to mem1 and subtract 2 from 50 to get 48
> ,         # Go to mem2 and take user input

# Now to get the actual value of input on mem2 subtract 48 from it
<        # Go to mem1 to use the value 48 as a counter
[
    > -  # Subtract 1 from mem2 48 times
< -
]        # After the loop mem2 will have the actual value of input
>> ,     # Go to mem3 and take second user input

# Now add the actual value of first input on the ascii value of second input using loop
<
[
    > +
< -
]    # Now we have the ascii value of the sum of the first input and second input on mem3

> .  # Go to mem3 and print sum
