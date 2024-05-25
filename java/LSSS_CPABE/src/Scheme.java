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

    /**
     * 
     * @methods: Static Trasnfer methods
     */
    // 定义包含所有十六进制字符的数组
    private static final char[] HEX_ARRAY = "0123456789ABCDEF".toCharArray();

    // 16进制的byte[]数组转换为字符串
    public static String hexBytesToString(byte[] bytes) {
        char[] hexChars = new char[bytes.length * 2];
        for (int j = 0; j < bytes.length; j++) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 2] = HEX_ARRAY[v >>> 4];
            hexChars[j * 2 + 1] = HEX_ARRAY[v & 0x0F];
        }
        return new String(hexChars);
    }

    // 16进制的字符串转换为byte[]数组
    public static byte[] hexStringToBytes(String s) {
        int len = s.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4) + Character.digit(s.charAt(i + 1), 16));
        }
        return data;
    }

    // 10进制数组转换为字符串
    public static String intToString(int[] arr) {
        StringBuilder sb = new StringBuilder();
        for (int i : arr) {
            sb.append(i);
        }
        return sb.toString();
    }
}
