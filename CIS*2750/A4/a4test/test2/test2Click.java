import java.awt.event.*;

/* ActionListener for "test2Click" button in test2
 * Writes 'Clicked!' to status area.
 */
public class test2Click implements ActionListener {

    test2FieldEdit dialog;

    public test2Click(test2FieldEdit dialog) {
        this.dialog = dialog;
    }

    public void actionPerformed(ActionEvent e) {
        dialog.appendToStatusArea("\nClicked!");
    }
}

