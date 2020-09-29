package electrifierzzz.robotcontrol;

import android.util.Base64;
import java.util.ArrayList;
import java.util.List;

public class PatternUtils {

    private PatternUtils() {}

    private static String bytesToString(byte[] bytes) {
        return Base64.encodeToString(bytes, Base64.NO_WRAP);
    }

    private static byte[] stringToBytes(String string) {
        return Base64.decode(string, Base64.DEFAULT);
    }

    public static byte[] patternToBytes(List<PatternView.Cell> pattern) {
        int patternSize = pattern.size();
        byte[] bytes = new byte[patternSize];
        for (int i = 0; i < patternSize; ++i) {
            PatternView.Cell cell = pattern.get(i);
            bytes[i] = (byte)(cell.getRow() * 3 + cell.getColumn());
        }
        return bytes;
    }

    public static List<PatternView.Cell> bytesToPattern(byte[] bytes) {
        List<PatternView.Cell> pattern = new ArrayList<>();
        for (byte b : bytes) {
            pattern.add(PatternView.Cell.of(b / 3, b % 3));
        }
        return pattern;
    }

    public static String patternToString(List<PatternView.Cell> pattern) {
        return bytesToString(patternToBytes(pattern));
    }

    public static List<PatternView.Cell> stringToPattern(String string) {
        return bytesToPattern(stringToBytes(string));
    }

}
