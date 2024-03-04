import utils
import secrets
from typing import List, Tuple
from sympy import nextprime
import gmpy2

BITS = 256


class Accumulator:
    """Accumulator Constructor"""

    def __init__(self, bits=BITS):
        self.bits = bits
        self.wits: List[int] = []
        self.pids: List[str] = []
        self.N: int = None
        self.secret_key: Tuple[int, int] = None
        # 累加器的生成元
        self.G: int = None
        self.acc_cur: int = None

    def setup(self):
        """初始化累加器"""
        # 生成一个随机数作为起点，然后找到下一个素数
        start_p = secrets.randbits(self.bits)
        p = nextprime(start_p)

        # 为了确保p和q不相等，可以再次执行类似的步骤来生成q
        start_q = secrets.randbits(self.bits)
        q = nextprime(start_q)

        # 确保p和q不相等，如果相等则重新生成q
        while q == p:
            start_q = secrets.randbits(self.bits)
            q = nextprime(start_q)

        self.G = secrets.randbits(self.bits)
        self.acc_cur = self.G
        self.N = p * q
        self.secret_key = (p, q)

    def add_member(self, pid: str):
        """添加成员到累加器中"""
        self.pids.append(pid)
        self.acc_cur = gmpy2.powmod(self.acc_cur, utils.hex2int(pid), self.N)

    def __witness_generate_by_pid(self, pid_val: str) -> int:
        """generate witness by pid"""
        product: int = 1
        for pid in self.pids:
            if pid == pid_val:
                continue
            else:
                product *= utils.hex2int(pid)
        witness: int = gmpy2.powmod(self.G, product, self.N)
        return witness

    def witness_generate_all(self):
        """添加完毕，生成所有成员的证据值"""
        for pid in self.pids:
            wit = self.__witness_generate_by_pid(pid)
            self.wits.append(wit)

    def verify_member(self, pid: str, wit: int) -> bool:
        """验证成员"""
        res: int = gmpy2.powmod(wit, utils.hex2int(pid), self.N)
        return res == self.acc_cur
    
    def remove_element_by_pid(self, pid: str):
        """移除成员 和 相应的证据值"""
        i = 0
        for p in self.pids:
            if p == pid:
                break
            i += 1
        self.pids.pop(i)
        self.wits.pop(i)
    
    def remove_member(self, pid: str) -> int:
        """移出成员，返回相应的更新值"""
        if pid in self.pids is False:
            raise ValueError("pid not in the member list")
        
        euler_pk: int = (self.secret_key[0] - 1) * (self.secret_key[1] - 1)
        aux: int = gmpy2.invert(utils.hex2int(pid), euler_pk)  
        
        self.acc_cur = gmpy2.powmod(self.acc_cur, aux, self.N)   
        self.remove_element_by_pid(pid)
         
        return aux
    


if __name__ == "__main__":
    acc = Accumulator()
    acc.setup()

    print(acc.N)
    print(acc.secret_key)
    print(acc.G)

    file_path = "./assets.json"
    pids: list = utils.load_from_json(file_path)
    for pid in pids:
        acc.add_member(pid)

    acc.witness_generate_all()

    for pid, wit in zip(acc.pids, acc.wits):
        print("pid: ", utils.hash2int(pid))
        print("wit: ", wit)
        print("verify: ", acc.verify_member(pid, wit))
        print("-------------------------------")
