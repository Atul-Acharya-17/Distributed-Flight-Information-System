package skeleton;

import java.util.HashMap;

public abstract class Skeleton {
    HashMap <String, byte[]> histroy = new HashMap<String, byte[]>();

    public abstract void handle(byte[] content, String clientIP, int port, int messageId);
}
