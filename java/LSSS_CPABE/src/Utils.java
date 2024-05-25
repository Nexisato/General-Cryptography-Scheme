
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


}
