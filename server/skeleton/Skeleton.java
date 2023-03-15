package skeleton;

import java.util.HashMap;

public abstract class Skeleton {
    protected static HashMap <String, byte[]> history = new HashMap<String, byte[]>();

    public static void handle(byte[] content, String clientIP, int port, int requestId){};
}
