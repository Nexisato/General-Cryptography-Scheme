import it.unisa.dia.gas.jpbc.Element;
import it.unisa.dia.gas.jpbc.Field;
import it.unisa.dia.gas.plaf.jpbc.pairing.a.TypeACurveGenerator;
import it.unisa.dia.gas.jpbc.Pairing;
import it.unisa.dia.gas.jpbc.PairingParameters;
import it.unisa.dia.gas.plaf.jpbc.pairing.PairingFactory;
import it.unisa.dia.gas.plaf.jpbc.pairing.a1.TypeA1CurveGenerator;
import it.unisa.dia.gas.plaf.jpbc.util.ElementUtils;
import java.io.*;

public class CPAPE extends Scheme {

    void init() {
        int rBit = 160;
        int qBit = 512;
        // Type A曲线
        TypeACurveGenerator pg = new TypeACurveGenerator(rBit, qBit);
        // // Type A1曲线
        // TypeA1CurveGenerator pg = new TypeA1CurveGenerator(numPrimes, qBit);
        PairingParameters typeAParams = pg.generate();
        Pairing bp = PairingFactory.getPairing(typeAParams);
        System.out.println(typeAParams);
        // 从文件a.properties中读取参数初始化双线性群

    }
}
