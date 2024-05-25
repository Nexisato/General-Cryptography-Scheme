import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.lang.String;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Utils {
    private static File _f_lib = new File(".\\lib");
    public static final Logger logger = LoggerFactory.getLogger(Utils.class);

    public static void recordJarFiles() throws IOException {
        File[] files = _f_lib.listFiles(new FilenameFilter() {
            public boolean accept(File dir, String name) {
                return name.endsWith(".jar");
            }
        });
        for (File file : files) {
            logger.debug(file.getName());
        }
    }

    public static long getDuration(long start, long end) {
        return end - start;
    }

    public static void printIntMatrix(int[][] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static void printStringMatrix(String[] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            System.out.println(matrix[i]);
        }
    }

    public static int[][] stringMatrixToInt(String[] v, int c) {
        int[][] res = new int[v.length][c];
        for (int i = 0; i < v.length; i++) {
            String[] splitLine = v[i].split(",");
            for (int j = 0; j < splitLine.length; j++) {
                res[i][j] = Integer.parseInt(splitLine[j]);
            }
        }
        return res;
    }

}
