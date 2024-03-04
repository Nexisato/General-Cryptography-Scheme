"""
Author: nexisato
Date: 2024-03-04 20:43:57
FilePath: /miracl_validation/python/benchmark.py
Description: 

"""

import utils
import time
from fastecdsa import point, curve, keys
import gmpy2
import secrets


def test_point_add(a: point.Point, b: point.Point, threshold: int):
    start = time.perf_counter()
    for _ in range(threshold):
        c = a + b
    end = time.perf_counter()
    print(
        f"[TEST] ec point point add time: {utils.get_duration(start, end) / threshold} ms"
    )


def test_point_mul(a: point.Point, q: int, threshold: int):
    start = time.perf_counter()
    for _ in range(threshold):
        b = secrets.randbelow(q)
        _ = b * a
    end = time.perf_counter()
    print(
        f"[TEST] ec point scalar mul time: {utils.get_duration(start, end) / threshold} ms"
    )


def test_pow_mod(bit_num: int, threshold: int):
    start = time.perf_counter()
    for _ in range(threshold):
        a = secrets.randbits(bit_num)
        b = secrets.randbits(bit_num)
        c = secrets.randbits(bit_num * 2)
        c = gmpy2.powmod(a, b, c)
    end = time.perf_counter()
    print(f"[TEST] gmpy2 powmod time: {utils.get_duration(start, end) / threshold} ms")


def test_hash2int(threshhold: int):
    start = time.perf_counter()
    for _ in range(threshhold):
        input_str: str = secrets.token_hex(256)
        _ = utils.hash256Function2int(input_str)
    end = time.perf_counter()
    print(f"[TEST] hash2int time: {utils.get_duration(start, end) / threshhold} ms")


if __name__ == "__main__":
    # ec_curve = curve.secp256k1
    # ec_P = ec_curve.G
    # ec_secret = keys.gen_private_key(ec_curve)
    # ec_Ppub = keys.get_public_key(ec_secret, ec_curve)
    # ec_q = ec_curve.q

    # test_point_add(ec_P, ec_P, 1000)
    # test_point_mul(ec_P, ec_q, 1000)

    # test_pow_mod(256, 1000)
    test_hash2int(1000)
