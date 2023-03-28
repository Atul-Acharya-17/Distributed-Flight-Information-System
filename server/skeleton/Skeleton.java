package skeleton;

import java.io.IOException;
import java.util.HashMap;

/*
    Abstract class skeleton which is dervied by every other skeleton.
    There is one skeleton for every functionality.
*/ 
public abstract class Skeleton {

    // Server type for experiments
    public enum ServerType {
        ATMOST_ONCE,
        ATLEAST_ONCE;
    }

    private static ServerType serverType = ServerType.ATMOST_ONCE;

    // History to save messages to retransmit on duplicate requests
    protected static HashMap <String, byte[]> history = new HashMap<String, byte[]>();

    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException {};
    
    // Respond to duplicates
    // Doesn't identify duplicates if the server type is Atleast Once 
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
    
    // Save the replies sent
    public static void storeResponse(byte[] response, String clientIP, int port, int requestId) throws IOException {
        String key = requestId + "@" + clientIP + ":" + port;
        history.put(key, response);
    };

    // Set server type
    public static void setServertype(ServerType st)
    {
        serverType = st;
    }
}
