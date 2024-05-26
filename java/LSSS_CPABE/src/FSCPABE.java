import it.unisa.dia.gas.jpbc.Element;
import it.unisa.dia.gas.jpbc.Field;
import it.unisa.dia.gas.plaf.jpbc.pairing.a.TypeACurveGenerator;
import it.unisa.dia.gas.jpbc.Pairing;
import it.unisa.dia.gas.jpbc.PairingParameters;
import it.unisa.dia.gas.plaf.jpbc.pairing.PairingFactory;
import it.unisa.dia.gas.plaf.jpbc.pairing.a1.TypeA1CurveGenerator;
import it.unisa.dia.gas.plaf.jpbc.util.ElementUtils;
import java.io.*;
import java.math.BigInteger;

import Jama.Matrix;

public class FSCPABE extends Scheme {
    TypeA1CurveGenerator pg = null;
    PairingParameters typeA1Params = null;
    Pairing pairing = null;
    private BigInteger N = null;
    private Field G = null;
    private Field GT = null;
    private Field Zr = null;
    private Element generator = null;
    private Element g = null;
    private Element g3 = null;
    private Element alpha = null;
    private Element a = null;
    private Element L = null;
    private Element C1 = null;
    private Element K = null;
    private Element[] u = null;
    private Element[] U = null;
    private Element[] Cx = null;
    private Element[] Dx = null;
    private Element[] C0 = null;
    private Element[] Ki = null;
    private Element egg = null;

    public static void main(String[] args) {
        FSCPABE fscpabe = new FSCPABE();
        fscpabe.init(4, 32);

        String S[] = { "A", "B", "C" };
        fscpabe.keygen(S);

    }

    public void init(int attriNum, int params) {
        this.pg = new TypeA1CurveGenerator(3, params);
        this.typeA1Params = pg.generate();
        System.out.println(typeA1Params);
        // e
        this.pairing = PairingFactory.getPairing(typeA1Params);
        this.generator = Scheme.getRandomFromG1(pairing);
        this.g = ElementUtils.getGenerator(this.pairing, this.generator, typeA1Params, 0, 3).getImmutable();
        // 私钥
        this.g3 = ElementUtils.getGenerator(this.pairing, this.generator, typeA1Params, 2, 3).getImmutable();

        // 生成G
        this.G = pairing.getG1();
        this.N = G.getOrder();
        this.Zr = pairing.getZr();
        // GxG->GT
        this.GT = pairing.getGT();
        this.alpha = Scheme.getRandomFromZp(this.pairing);
        this.a = Scheme.getRandomFromZp(this.pairing);
        // e(g,g)
        this.egg = pairing.pairing(g, g).getImmutable();
        // 为属性空间每个属性选取随机值
        this.u = new Element[attriNum];
        for (int i = 0; i < attriNum; i++) {
            u[i] = Scheme.getRandomFromZp(pairing);
        }
        this.U = new Element[attriNum];
        for (int i = 0; i < attriNum; i++) {
            U[i] = g.powZn(u[i]).getImmutable();
        }

    }

    public void keygen(String[] S) {
        Element R = ElementUtils.getGenerator(this.pairing, this.generator, this.typeA1Params, 2, 3).getImmutable();
        Element R1 = ElementUtils.getGenerator(this.pairing, this.generator, this.typeA1Params, 2, 3).getImmutable();

        Element[] Ri = new Element[S.length];
        for (int i = 0; i < S.length; i++) {
            Ri[i] = ElementUtils.getGenerator(this.pairing, this.generator, this.typeA1Params, 2, 3).getImmutable();
        }

        Element t = Scheme.getRandomFromZp(this.pairing);
        this.K = this.g.powZn(this.alpha).mul(this.g.powZn(this.a.mul(t))).mul(R).getImmutable();
        this.L = this.g.powZn(t).mul(R1).getImmutable();

        this.Ki = new Element[S.length];
        for (int i = 0; i < S.length; i++) {
            this.Ki[i] = this.U[i].powZn(t).mul(Ri[i]).getImmutable();
        }
    }
}
