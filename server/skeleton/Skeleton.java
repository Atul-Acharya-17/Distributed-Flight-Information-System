package skeleton;

import java.io.IOException;
import java.util.HashMap;

public abstract class Skeleton {
    protected static HashMap <String, byte[]> history = new HashMap<String, byte[]>();

    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException {};
    
    public static boolean checkandRespondToDuplicate(byte[] content, String clientIP, int port, int requestId) throws IOException {
        String key = requestId + "@" + clientIP + ":" + port;
        if (history.containsKey(key)) {
            communication.Communication.send(clientIP, port, history.get(key));
            return true;
        }
        return false;
    };
    
    public static void storeResponse(byte[] response, String clientIP, int port, int requestId) throws IOException {
        String key = requestId + "@" + clientIP + ":" + port;
        history.put(key, response);
    };
}
