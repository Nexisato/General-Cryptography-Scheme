import java.math.BigInteger;
import java.security.MessageDigest;
import it.unisa.dia.gas.jpbc.Element;
import it.unisa.dia.gas.jpbc.Pairing;

public abstract class Scheme {
    /**
     * 
     * @methods: Static Get Element methods
     */

    // G1中获取随机元素，获取1，获取0
    public static Element getRandomFromG1(Pairing pairInstance) {
        return pairInstance.getG1().newRandomElement().getImmutable();
    }

    public static Element getOneFromG1(Pairing pairInstance) {
        return pairInstance.getG1().newOneElement().getImmutable();
    }

    public static Element getZeroFromG1(Pairing pairInstance) {
        return pairInstance.getG1().newZeroElement().getImmutable();
    }

    // Zr中获取随机元素，获取1，获取0
    public static Element getRandomFromZp(Pairing pairInstance) {
        return pairInstance.getZr().newRandomElement().getImmutable();
    }

    public static Element getOneFromZp(Pairing pairInstance) {
        return pairInstance.getZr().newOneElement().getImmutable();
    }

    public static Element getZeroFromZp(Pairing pairInstance) {
        return pairInstance.getZr().newZeroElement().getImmutable();
    }

    /**
     * 
     * @methods: Static Hash methods
     */

    // H(·) : String → Zp
    public static Element hashFromStringToZp(Pairing pairInstance, String str) {
        return pairInstance.getZr().newElement().setFromHash(str.getBytes(), 0, str.length()).getImmutable();
    }

    // H(·) : {0, 1}* → Zp
    public static Element hashFromBytesToZp(Pairing pairInstance, byte[] bytes) {
        return pairInstance.getZr().newElement().setFromHash(bytes, 0, bytes.length).getImmutable();
    }

    // H(·) : G1 → Zp
    public static Element hashFromG1ToZp(Pairing pairInstance, Element g1_element) {
        // h(y) : G1 -> Zp
        byte[] g1_bytes = g1_element.getImmutable().toCanonicalRepresentation();
        byte[] zp_bytes = g1_bytes;
        try {
            MessageDigest hasher = MessageDigest.getInstance("SHA-512");
            zp_bytes = hasher.digest(g1_bytes); // 先把G1元素hash成512bits
        } catch (Exception e) {
            e.printStackTrace();
        }
        // 再把hash后的bits映射到Zp
        Element hash_result = pairInstance.getZr().newElementFromHash(zp_bytes, 0, zp_bytes.length).getImmutable();
        return hash_result;
    }

    // H(·) : GT → Zp
    public static Element transformFromGtToZp(Pairing pairInstance, Element pairing_result) {
        BigInteger pairing_params = pairing_result.toBigInteger();
        return pairInstance.getZr().newElement().set(pairing_params);
    }
}
