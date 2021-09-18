# keysubtracter
Bitcoin and Altcoins Publickey subtracter

Generate multiple but different "copies" of a publickey, Actually Added and substracted publickeys.

Post: https://bitcointalk.org/index.php?topic=5360656.0

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

## Generate hashes rmd160 of the publickey
With the parameter `-f rmd160` you can select the format of the output

```./keysubtracter -p 02ceb6cbbcdbdf5ef7150682150f4ce2c6f4807b349827dcdbdd1f2efa885a2630 -n 10 -r 0:32 -f rmd160
682c50abbc29474dba1f5a5b49e8a2cdc8ec9515 # - 10
6aca33ba1636394c01606fb15ed4e3ca90d62267 # + 10
4c8a3be7643ac4fa10380f74fa32e02ec9751a4e # - 20
e5a8c3aade6998a2890ade3bdba058eaf3f76c3e # + 20
03f9243592bf038dc4bbbb5a1f7f91dbc52f4971 # - 30
44e75c4a6fcece151aa47ebf6a1381c959ecc337 # + 30
4edcf7c0078162514b645acd7073dcc63735f12e # - 40
22510f1ed8898ebb0f084ceda94b3c284ddbe05a # + 40
eabea28b06974094a9b5be9bc89d3b53c346a13e # - 50
ca051a1de4828bfab450b5f4570869187dc05138 # + 50
4b46e10a541aeec6be3fac709c256fb7da69308e # target
```

## Generate address of the publickey
With the parameter `-f address` you can select the format of the output
```./keysubtracter -p 02ceb6cbbcdbdf5ef7150682150f4ce2c6f4807b349827dcdbdd1f2efa885a2630 -n 10 -r 0:32 -f address
1AVpN26dFDuMS2YwseUMaJ794XjMxb14ry # - 10
1AjerabryCRsi8PQmyeqVmwqn5jMVGrf1j # + 10
17yhxFFoMHRqCpk2qwmCYU4shZFz7Pq9Bd # - 20
1MwKut3gKEqTctLL8SL1M5gPG5PsW3ntat # + 20
1N1VE8aLcq9TiBQZVetFVT2F9nrnWVxQu # - 30
17HL7FmQ61r5ieDhbDh6WEKZBKcohmux9U # + 30
18BzR5E6vsweQpwJcJb9ov2c2BWTxZ11Yd # - 40
148T5c5SLwDK4uGKhGHRy3x4y7wBQrYmRC # + 40
1NQDVSGomQk3hWhc5yVrXjpPJTDX83bqCb # - 50
1KRBcFAXzd3ij9BxjyM5gFreDZc2tpcNw8 # + 50
17s2b9ksz5y7abUm92cHwG8jEPCzK3dLnT # target
```

## Removing the comment information
Just add the parameter `-x` to hide the comment from the output. For non random substraction this will be ok, but for Random substractions you need to keep that information of the offset because if you hit some privatekey you need that information to get the targer privatekey back.

```
./keysubtracter -p 02ceb6cbbcdbdf5ef7150682150f4ce2c6f4807b349827dcdbdd1f2efa885a2630 -n 10 -r 0:32 -f address -x
1AVpN26dFDuMS2YwseUMaJ794XjMxb14ry
1AjerabryCRsi8PQmyeqVmwqn5jMVGrf1j
17yhxFFoMHRqCpk2qwmCYU4shZFz7Pq9Bd
1MwKut3gKEqTctLL8SL1M5gPG5PsW3ntat
1N1VE8aLcq9TiBQZVetFVT2F9nrnWVxQu
17HL7FmQ61r5ieDhbDh6WEKZBKcohmux9U
18BzR5E6vsweQpwJcJb9ov2c2BWTxZ11Yd
148T5c5SLwDK4uGKhGHRy3x4y7wBQrYmRC
1NQDVSGomQk3hWhc5yVrXjpPJTDX83bqCb
1KRBcFAXzd3ij9BxjyM5gFreDZc2tpcNw8
17s2b9ksz5y7abUm92cHwG8jEPCzK3dLnT
```

## Misc
In case of hit one privatekey the information that you need to calculate the target privatekey back is the next:
- original publickey target `-p publickey`
- range `-r A:B` or bit number `-b number`
- number of items requested `-n number`
- privatekey found

I will make some other tool in this project to calculate back the target privatekey in case of hit one of the subtracted values.

## Donations

- BTC: 1Coffee1jV4gB5gaXfHgSHDz9xx9QSECVW
- ETH: 0x6222978c984C22d21b11b5b6b0Dd839C75821069
- DOGE: DKAG4g2HwVFCLzs7YWdgtcsK6v5jym1ErV
- BCB: bcb_3rf4pzhrdeziygir8t5pmep4xdwqwyk1xgmytzyo991gdez1sgq1ehb3a8jh
