package skeleton;

import java.io.IOException;
import java.util.HashMap;

public abstract class Skeleton {

    public enum ServerType {
        ATMOST_ONCE,
        ATLEAST_ONCE;
    }

    private static ServerType serverType = ServerType.ATMOST_ONCE;

    protected static HashMap <String, byte[]> history = new HashMap<String, byte[]>();

    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException {};
    
    public static boolean checkandRespondToDuplicate(byte[] content, String clientIP, int port, int requestId) throws IOException {
        if (serverType == ServerType.ATLEAST_ONCE) return false;

        String key = requestId + "@" + clientIP + ":" + port;
        if (history.containsKey(key)) {
            System.out.println("Sending Duplicate Reply");
            communication.Communication.send(clientIP, port, history.get(key));
            return true;
        }
        return false;
    };
    
    public static void storeResponse(byte[] response, String clientIP, int port, int requestId) throws IOException {
        String key = requestId + "@" + clientIP + ":" + port;
        history.put(key, response);
    };

    public static void setServertype(ServerType st)
    {
        serverType = st;
    }
}
