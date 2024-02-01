# First get the ascii value of 0 which is 48 on
# mem1 mem2 and mem3 using mem0 as a counter
# Use mem4 and mem5 for uset input
# Use mem3 to compute the product of the user inputs

+++++
[
    > +++++ +++++     # mem1
    > +++++ +++++     # mem2
	> +++++ +++++     # mem3
<<< -
]           # After the loop mem1 mem2 and mem3 are 50
> --        # Go to mem1 and subtract 2 from 50 to get 48
> --        # Go to mem2 and subtract 2 from 50 to get 48
> --        # Go to mem3 and subtract 2 from 50 to get 48
> ,         # Go to mem4 and take first user input
> ,         # Go to mem5 and take second user input


# Now lets subtract mem1(48) from mem4 to get the actual value of first input
<<<<       # Go to mem1 to use the value 48 as a counter
[
    >>> -  # Subtract 1 from mem4 48 times
<<< -
]         # After the loop mem4 will have the actual value of first input
# We are now currently in mem1


# Now lets subtract mem2(48) from mem5 to get the actual value of second input
>         # Go to mem2 to use the value 48 as a counter
[
    >>> -  # Subtract 1 from mem5 48 times
<<< -
]         # After the loop mem5 will have the actual value of second input
# We are now currently in mem2


# To compute the product we must add the value in mem5 which is the second
# user input to the ascii value of 48 on mem3 repeatedly using the value mem4
# which is the first user input

# To do this we need the value of mem5 always in each loop so we will make it
# so that mem6 will always has this value by duplicate back and forth between
# mem5 and mem7

>>       # Go to mem4
[
	>  # go to mem5 and duplicate its value on mem6 and mem7
	[
		> +    # Go to mem6 and duplicate
		> +    # Go to mem7 and duplicate
	<< -
	]    # Now we have a duplicate value at mem6 and mem7
	# Currently at mem5

	# Add mem6 on mem3
	>    # Initially at mem6
	[
		<<< +
	>>> -
	]
	# Currently at mem6

	# Now duplicate mem7 to mem5 to get a constant value at mem6 on the
	# next loop
	>    # Go to mem7
	[
		<< +
	>> -
	]
	# Currently at mem7

<<< -
]
# We are currently at mem4
< .          # Print the product on mem3
