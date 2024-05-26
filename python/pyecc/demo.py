# secp256k1 生成公钥
# 利用标量乘法，从私钥生成公钥
from py_ecc.secp256k1 import secp256k1
import os 

def generate_public_key(private_key):
    """
    使用secp256k1椭圆曲线，根据给定的私钥生成公钥。
    
    参数:
    private_key (int): 私钥，一个大整数。
    
    返回:
    (int, int): 公钥，椭圆曲线上的点。
    """
    # secp256k1的基点
    G = secp256k1.G
    
    # 计算公钥
    public_key = secp256k1.multiply(G, private_key)
    
    return public_key

# 示例：使用一个随机的私钥
private_key = int(os.urandom(32).hex(), 16)

# 生成公钥
public_key = generate_public_key(private_key)

# 打印结果
print(f"Private Key: {private_key}")
print(f"Public Key: {public_key}")

# 示例输出
# Private Key: 40871478222817722377012551921323657605236631423958081783403470740144884256441
# Public Key: (18814187692496112820586797121940816605467606938301853840004393937958984136992, 72833048843328294920821861725991661253504985018641366317346599320677055943891)
