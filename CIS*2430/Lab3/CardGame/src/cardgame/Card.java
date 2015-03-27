/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cardgame;

/**
 *
 * @author michaelsadowski
 */
public class Card {

    public enum Suit {

        SPADES, HEARTS, CLUBS, DIAMONDS
    }
    private Suit suit;
    private Object image;
    private static Object backImage;
    private int rank;
    private boolean faceUp;

    public Card(Suit suit, int rank) {
        this.suit = suit;
        this.rank = rank;
    }

    public int getRank() {
        return rank;
    }

    public Suit getSuit() {
        return suit;
    }

    public void setFaceup(boolean faceUp) {
        this.faceUp = faceUp;
    }

    public boolean getFaceup() {
        return faceUp;
    }

    public Object getImage() {
        return image;
    }

    public void setImage(Object image) {
        this.image = image;
    }

    public static void setBackImage(Object image) {
        backImage = image;
    }

    public static Object getBackImage() {
        return backImage;
    }

    public String toString() {

        return suit + "" + rank;
    }
@Override public boolean equals(Object other) {
    boolean result = false;
    if (other instanceof Card) {
        Card that = (Card) other;
        result = (this.getRank() == that.getRank());
    }
    return result;
    }   

}

