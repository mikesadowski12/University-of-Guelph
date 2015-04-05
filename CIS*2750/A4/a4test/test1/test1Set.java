import java.awt.event.*;

/* ActionListener for "test1Set" button in test1
 * Attempts to put value in Integer1 field. Shouldn't write "FAIL" message to status area.
 * Attempts to put value in Float1 field. Shouldn't write "FAIL" message to status area.
 * Attempts to put value in String1 field. Shouldn't write "FAIL" message to status area.
 */
public class test1Set implements ActionListener {

    test1FieldEdit dialog;

    public test1Set(test1FieldEdit dialog) {
        this.dialog = dialog;
    }

    public void actionPerformed(ActionEvent e) {
        try {
            dialog.setDCInteger1("123");
        } 
        catch(Exception ex) {
            dialog.appendToStatusArea("\nFAIL: Integer1 was incorrectly rejected");
        }

        try {
            dialog.setDCFloat1("123.0");
        } 
        catch(Exception ex) {
            dialog.appendToStatusArea("\nFAIL: Float1 was incorrectly rejected");
        }

        try {
            dialog.setDCString1("PASS");
        } 
        catch(Exception ex) {
            dialog.appendToStatusArea("\nFAIL: String1 was incorrectly rejected");
        }
    }
}

