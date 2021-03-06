.name "Zork_Killer"
.comment "Initial version of the champion"

create:
live %1
ld      5,  r2
st      r1, 427
st      r1, 442
st      r1, 457
st      r1, 472
st      r1, 487
st      r1, 502
fork    %:end_lb

too_crt:
live    %1
ld      5,  r3
st      r2, 389
st      r3, 404
st      r3, 419
st      r2, 434
st      r3, 449
st      r2, 464
fork    %:create

jumping:
live    %1
ld      5,  r4
st      r3, 351
st      r4, 366
st      r4, 381
st      r3, 396
st      r4, 411
st      r3, 426
zjmp    %:seven_lb

too_jmp:
live    %1
ld      5,  r5
st      r4, 313
st      r5, 328
st      r5, 343
st      r4, 358
st      r5, 373
st      r3, 388
zjmp    %:five_lb

five_lb:
live    %1
ld      5,  r6
st      r6, 375
st      r5, 390
st      r5, 405
st      r6, 420
st      r6, 435
st      r5, 450
zjmp    %:too_crt

six_lb:
live    %1
ld      5,  r7
st      r7, 337
st      r6, 352
st      r6, 367
st      r6, 382
st      r7, 397
st      r6, 412
zjmp    %:create

seven_lb:
live    %1
ld      5,  r8
st      r7, 299
st      r7, 314
st      r8, 329
st      r8, 344
st      r8, 359
st      r8, 374
zjmp    %:jumping

copy:
live    %1
ld      5,  r9
st      r9, 261
st      r8, 276
st      r9, 291
st      r9, 306
st      r8, 321
st      r8, 336
zjmp    %:create

end_lb:
live    %1
ld      5,  r10
st      r9, 323
st      r10, 323
st      r10, 323
live    %42
st      r15, 33
st      r15, 33
st      r15, 33
st      r15, 33
st      r15, 33
st      r15, 33
zjmp    %:too_crt
