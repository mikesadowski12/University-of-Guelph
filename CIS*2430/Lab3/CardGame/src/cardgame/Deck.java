/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cardgame;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.*;
/**
 *
 * @author michaelsadowski
 */
public class Deck {
    private ArrayList<Card> myDeck;
    
    public Deck(){
        myDeck = new ArrayList<Card>();

        for (int i = 1; i < 14; i++){
            myDeck.add( new Card(Card.Suit.SPADES,i) );
            myDeck.add( new Card(Card.Suit.HEARTS,i) );
            myDeck.add( new Card(Card.Suit.DIAMONDS,i) );
            myDeck.add( new Card(Card.Suit.CLUBS,i) );
        }
        
    }
    
    public void shuffle(){
        Collections.shuffle(myDeck);
    }
    public ArrayList<Card> getCards(){
        return myDeck;
    }
    
}
