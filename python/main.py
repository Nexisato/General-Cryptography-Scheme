"""
Author: nexisato
Date: 2024-03-04 11:34:04
FilePath: /py_validation/main.py
Description: 

"""

from kgc import KGC
from entity import Entity, Payload
import utils
from fastecdsa import curve, keys, point
import gmpy2
import datetime


acc_cur: str = (
    "16d09945c33747913fddf4ddb8fc0fe9548676ea060f47901d8acdc35e7476637fdcba2cb3d71fe0b09848c77ba82579b39b39a754d4d86d2031797dae92a40f"
)
N_str: str = (
    "256ab0535223b7f396e9a83baf495485643f53fe0b169abbf9c65f319a90f11fd9d6e742bc96511164a482acad9fbd3436908ab81b80ec400738175539d10e11"
)
pid1: str = "5158ee15ec9beeae6cfcb3c5728e4313"
wit1: str = (
    "7154a3d17795d52ffb0e22f3d34c01c4134c544f3367f208f2d6c80dd6750128bfe7f672a642a9c4a3ed644543330467e8751f3b2a80e53ca978f3a74aca0d4"
)
pid2: str = "12767b506ebefbacab00b1f080737958f"


def hex2int(hex: str) -> int:
    """convert hex string to int"""
    return int(hex, 16)


def test_acc(acc: str, pid: str, wit: str, N: str):

    res = utils.quick_pow(wit, pid, N)
    print("res: ", res)
    acc_res = gmpy2.mpz(acc, 16)
    print("acc: ", acc_res)

    print("type of res: ", type(res))


if __name__ == "__main__":

    # test_acc(acc_cur, wit1, pid1, N_str)

    # 1. Initialize KGC
    kgc = KGC()

    print("s: ", kgc.s)
    print("Ppub: ", kgc.Ppub)
    print("P: ", kgc.P)

    print("s * P: ", kgc.s * kgc.P)
    print("s * P == Ppub?: ", kgc.s * kgc.P == kgc.Ppub)

    print("----------------- [2] Generate Partial Key -----------------")

    # 2. Generate partial key

    entity1 = Entity(pid1, curve.secp256k1, kgc.Ppub)

    #######

    entity2 = Entity(pid2, curve.secp256k1, kgc.Ppub)

    partial_key1 = kgc.generate_partial_key(pid1)
    print("r: ", partial_key1[0])
    print("R: ", partial_key1[1])

    print("----------------- [3] Generate Full Key -----------------")

    # 3. Generate full key
    flag: bool = entity1.generate_full_key(partial_key1[0], partial_key1[1])
    if flag:
        print("secret_key: ", entity1.secret_key)
        print("public_key: ", entity1.public_key)

    # 4. Sign
    print("----------------- [4] Entity1 sign the msg -----------------")
    msg1: str = "hello world"
    payload1 = entity1.sign(msg1, utils.hex2int(wit1), utils.hex2int(N_str))
    # print("raw_wit1: ", utils.hex2int(wit1))
    # print("payload1: ", payload1.wit_new)
    print("payload1.ti: ", payload1.time_stamp)

    # 5. Verify
    print("----------------- [5] Entity2 verify the msg -----------------")
    entity2.verify(payload1, utils.hex2int(acc_cur), utils.hex2int(N_str))
