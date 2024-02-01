# Take user input
# ==========================================================
> ,         # First input on mem 1
> ,         # First input on mem 2
<<          # Return to mem 0

# Get actual values of user input
# ==========================================================
# Convert input from ascii to actual value by subtracting 48 from both
# 48 is the ascii value of 0
+++++ +
[
    > ----- ---
    > ----- ---
    << -
]

# Multiply numbers
# ==========================================================
# Now we are at mem 0
>       # Go to mem1 and use it as a counter
[
	>  # go to mem2 and duplicate its value on mem3 and mem4
	[
		> +    # Go to mem3 and duplicate
		> +    # Go to mem4 and duplicate
	<< -
	]    # Now we have a duplicate value at mem3 and mem4
	# Currently at mem2

	# move mem3 to mem2
	>    # Initially at mem2 so go to mem3
	[
		< +
	> -
	]
	# Currently at mem3

<< -   # Go to mem1 and decrement counter
]
# Currently at mem1 and the product is now at mem4

# Separate the product at mem4 into its ones and tenth digit
# ==========================================================
>[-]                # Clear mem2
>+                  # Go to mem3 and add 1 
                    # mem3 is used to keep track of the tenth digit
>> +++++ +++++      # Go to mem5 and add 10
                    # mem5 is used to keep track of the difference of 10 and the ones digit 
                    # You will get the meaning after the loop
<       # Go to mem4 and use it as a counter
[
    -       # Decrement one from mem4
    > -     # Go to mem5 and decrement one
    [>>>]   # Find a free space 3 points down
    +++++ +++++     # Add 10 to it
    << +            # Go 2 back and 1 to it
    [<<<]   # Go back 3 points at a time and this will take you to mem0
    >>>>    # Go to mem4
]
# After the loop you are at mem4 but you need to do one more thing and that is
# to subtract one from mem3 to get the tenth digit
< -     # Subtract one from mem3         

# Now inorder to get the ones digit we need to subtract 10 from mem 5
# so lets use mem2 to hold the tenth digit
< +++++ +++++   # Go to mem2 and add 10
>>>             # Go to mem5
[
    -       # subtract one from mem5
    <<< -   # Go back to mem2 and subtract 1
    >>>     # Then go to mem5
]
# Currently at mem5
# Okay now we have successfully separated the product to its ones and tenth
# digit where the ones digit is at mem2 and the tenth digit is at mem5

# Now convert the tenth and ones digits to ascii
# ==========================================================
< +++++ +   # Go to mem4 and add 6 to use as a counter
[
    < +++++ +++     # Add 8 to mem3 6 times
    < +++++ +++     # Add 8 to mem2 6 times
    >> -            # Go to mem4 and decrement counter
]
# Currently at mem4

# Print result
# ==========================================================
< .     # Print tenth digit
< .     # Print ones digit
< +++++ +++++ . # Print new line
