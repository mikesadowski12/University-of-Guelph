import java.awt.event.*;

/* ActionListener for "test1Get" button in test1
 * Attempts to get value from Integer1 field. Should write value if valid. Should write 'Incorrect type' if invalid.
 * Attempts to get value from Float1 field. Should write value if valid. Should write 'Incorrect type' if invalid.
 * Attempts to get value from String1 field. Should write value if valid. Should write 'Incorrect type' if invalid.
 */
public class test1Get implements ActionListener {

    test1FieldEdit dialog;

    public test1Get(test1FieldEdit dialog) {
        this.dialog = dialog;
    }

    public void actionPerformed(ActionEvent e) {
        try {
            dialog.appendToStatusArea("\nInteger1 = " + dialog.getDCInteger1());
        }
        catch(Exception ex) {
            dialog.appendToStatusArea("\nInteger1 = Incorrect type");
        }

        try {
            dialog.appendToStatusArea("\nFloat1 = " + dialog.getDCFloat1());
        }
        catch(Exception ex) {
            dialog.appendToStatusArea("\nFloat1 = Incorrect type");
        }

        try {
            dialog.appendToStatusArea("\nString1 = " + dialog.getDCString1());
        }
        catch(Exception ex) {
            dialog.appendToStatusArea("\nString1 = Incorrect type");
        }
    }
}

