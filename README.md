# keysubtracter
Bitcoin and Altcoins Publickey subtracter

Generate multiple but different "copies" of a publickey, Actually Added and substracted publickeys.

Download, clone this repository:

`git clone https://github.com/albertobsd/keysubtracter.git`

Compile:

`make`

## Make copies of any publickey

This copies are generated at different offset of the orginal publickey.

For example to make 100 copies of the puzzle 120 you need to execute the next command:

`./keysubtracter -p 02ceb6cbbcdbdf5ef7150682150f4ce2c6f4807b349827dcdbdd1f2efa885a2630 -n 100 -b 120`

this will create 100 subtracted publickeys, well this is 50 Added publickeys and 50 substracted publickeys

## How the generated publickeys will be distributed?

Almost the half of those publickey will land in the 120 bits space `-b 120` becuase the input publickey supposedly is located in bitspace 119-120

And the 50 Upper keys are distributed in the 120 bit space divided by 50 upper the Original publickey
And the 50 Lower keys are distributed in the 120 bit space divided by 50 lower the original publickey

## How i can generated publickeys separated by a specific difference ?

Well to avoid add extra modifications to the code for now this need to be calculated with the current parameters.

if you want to generate 10 publickeys separated each with 10 of difference you need to specify a range of 100 divided by 2 with `-r 0:32` 32 hexadecimal is 50 decimal

`./keysubtracter -p 02ceb6cbbcdbdf5ef7150682150f4ce2c6f4807b349827dcdbdd1f2efa885a2630 -n 10 -r 0:32`

Example output:

```
023e40191ed19ba1c82d3948ffad7d11efc7352e8a071b09750fc0a62cba295f15 # - 10
02ad82cfd538d8f9a98ea7d2393a958962d3dd783456284353084ad74e459ca98c # + 10
029649575661e11d5c7c277d008c7a6d6a56c14824e31673a5a49809f94777858e # - 20
02a1c7e1fffa740388689234491047208e0f7c23a9bee61b61ef035a6d016a709c # + 20
02a3c299147e9cb77fc03b13712700361b6175e3fa3521a297854c73f680f8b389 # - 30
028a6ee5e557bf738107e02cf5533dd40d6390f4a4a1539092774246c1352583b8 # + 30
03911f949fe7d1c81152974161306cda43c810ec50839cee0ff1fd047b25eb95bf # - 40
0311d6b86415d2122e4103d63906cfda90f9f6359f2b90887839b25a2fe7e6de6b # + 40
02c234090ac778e0e311d4306a9ba41e042900f44f7166e3a17786e4376bfdfabf # - 50
039f147c6939d4d3b66eb7ae37f67652d1b4e28794a55ca39e22db6eb2c8949505 # + 50
02ceb6cbbcdbdf5ef7150682150f4ce2c6f4807b349827dcdbdd1f2efa885a2630 # target
```

Not clear how to calculate the range this is the formula

`(number keys that you want * expected difference )  bewteen two`

## How i can use those copies ?

You can use it in any program that accept multiple publickeys for cracking, kangaroo, BSGS of JPL or in my keyhunt with modes `bsgs` or `xpoint`

## Can i generated publickeys at random offset

Yes with `-R` but is a slow method because it use Scalar multiplication instead Point Addition

## Donations

- BTC: 1Coffee1jV4gB5gaXfHgSHDz9xx9QSECVW
- ETH: 0x6222978c984C22d21b11b5b6b0Dd839C75821069
- DOGE: DKAG4g2HwVFCLzs7YWdgtcsK6v5jym1ErV
- BCB: bcb_3rf4pzhrdeziygir8t5pmep4xdwqwyk1xgmytzyo991gdez1sgq1ehb3a8jh
