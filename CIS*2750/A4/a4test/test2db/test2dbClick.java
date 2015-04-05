import java.awt.event.*;

/* ActionListener for "test2dbClick" button in test2db
 * Writes 'Clicked!' to status area.
 */
public class test2dbClick implements ActionListener {

    test2dbFieldEdit dialog;

    public test2dbClick(test2dbFieldEdit dialog) {
        this.dialog = dialog;
    }

    public void actionPerformed(ActionEvent e) {
        dialog.appendToStatusArea("\nClicked!");
    }
}

