/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package cardgame;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
/**
 *
 * @author tao
 */
public class CardGame {
    private static final int SLEEPING_TIME = 5;
    private static final String TEXT_SHUFFLE = "Shuffle";
    private static final String TEXT_FLIP = "Flip";
    private static final String TEXT_MATCH = "Match";
    private static final String TEXT_ENDGAME = "End Game";
    private static final String TEXT_BINGO= "Bingo!";
    private static final String TEXT_OOPS = "Ooops!";
    private static final String TEXT_TITLE = "Find Matching!";
    private static final String TEXT_CARD_PROP = "CARD";
    
    private static  Deck deck;
    private static JPanel controlPanel;
    private static  ArrayList<JButton> cardButtons;
    private static JButton flipButton;
    private static JButton shuffleButton;
    private static JButton matchButton;
    private static JPanel deckPanel;
    private static JPanel contentPanel;
    private static Card  openCard = null;
    private static JFrame window;
    private static boolean gameStarted = false;
    private static int     attempts = 0;
    
    private static class EventHandler implements ActionListener {
      @Override
      public void actionPerformed(ActionEvent e) {
         if(cardButtons.contains(e.getSource())){
             JButton btnCard = (JButton)e.getSource();
            flipCard(btnCard);
            if(matchButton.getText().equalsIgnoreCase(TEXT_ENDGAME)){
                attempts++;
                if (openCard.equals(btnCard.getClientProperty(TEXT_CARD_PROP)))
                    JOptionPane.showMessageDialog(null,TEXT_BINGO + " "
                            + " After " + attempts + " attempts", TEXT_TITLE,JOptionPane.INFORMATION_MESSAGE);
                else{
                    JOptionPane.showMessageDialog(null,TEXT_OOPS,TEXT_TITLE,JOptionPane.ERROR_MESSAGE);
                    flipCard(btnCard);
                }
            }
         }
         else if(e.getSource() == flipButton)
            fliCards();
         else if(e.getSource() == shuffleButton)
             shuffle();
         else if(e.getSource() == matchButton){
             boolean gameStarted = matchButton.getText().equalsIgnoreCase(TEXT_ENDGAME);
             matchButton.setText(gameStarted?TEXT_MATCH:TEXT_ENDGAME);
             if(!gameStarted)
                 equalGame();
             shuffleButton.setEnabled(gameStarted);
             flipButton.setEnabled(gameStarted);
         }
      }
    }
    /**
     * @param args the command line arguments
     */    
    public static void main(String[] args) {
        //create a deck of cards
        deck = new Deck();
       
        //load images for cards
        cardButtons = new ArrayList<>();
        Card.setBackImage(new ImageIcon("images/b1fv.png"));
        for(int i = 0; i<deck.getCards().size(); i++){
            Card card = deck.getCards().get(i);
            String strCard = card.toString();
            card.setImage(new ImageIcon("images/"+strCard+".png"));            
        }        

        //create control buttons and control panel
        EventHandler listener = new EventHandler();        
        flipButton = new JButton(TEXT_FLIP);
        flipButton.addActionListener(listener);        
        shuffleButton = new JButton(TEXT_SHUFFLE);   
        shuffleButton.addActionListener(listener);
        matchButton = new JButton(TEXT_MATCH);
        matchButton.addActionListener(listener); 
        
        controlPanel = new JPanel(); 
        controlPanel.setLayout(new FlowLayout());
        controlPanel.setBorder(BorderFactory.createLineBorder(Color.GRAY));
        controlPanel.add(matchButton, FlowLayout.LEFT);
        controlPanel.add(flipButton, FlowLayout.LEFT);
        controlPanel.add(shuffleButton, FlowLayout.LEFT);

        
        //create the panel that accomondates the cards 
        deckPanel = new JPanel();
        
        //create GUI components for cards
        for (Card card : deck.getCards()) {
            JButton btn = new JButton();
            cardButtons.add(btn);            
            btn.addActionListener(listener);
            btn.setBorderPainted(false); //avoid border line
            btn.setPreferredSize(new Dimension(72,96)); //avoid excessive button border
            deckPanel.add(btn);
        }
        
        //binding GUI components to cards
        bindingCards2Buttons();

        //create the GUI panel that accomondates deckPanel and controlPanel
        contentPanel = new JPanel(); 
        contentPanel.setLayout(new BorderLayout());
        contentPanel.add(controlPanel,BorderLayout.NORTH);
        contentPanel.add(deckPanel,BorderLayout.CENTER);        
        
        //create the main window
        window = new JFrame("CIS*2430Lab - " + TEXT_TITLE);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setContentPane(contentPanel);
        window.setSize(1070,550);
        window.setLocationRelativeTo(null);
        window.setResizable(false);
        window.setVisible(true);        

    }
    /*
    private void distribute(Deck deck, ArrayList<Hand> players){
        for(int i = 0; i<deck.getCards().size(); i++)
            players.get(i%players.size()).addCard(deck.getCards().get(i));
    }
    */
    private static void fliCards(){
        cardButtons.stream().forEach((btn) -> {
            flipCard(btn);
        });        
    }
    
    private static void flipCard(JButton btnCard){
        Card card = (Card)btnCard.getClientProperty(TEXT_CARD_PROP);
        card.setFaceup(!card.getFaceup());             
        btnCard.setIcon((ImageIcon)(card.getFaceup()?card.getImage():Card.getBackImage()));        
    }
    
    private static void shuffle(){
        deck.shuffle();
        bindingCards2Buttons(); //re-binding cards to GUI components
    }
    private static void bindingCards2Buttons(){
        for(int i = 0; i<deck.getCards().size(); i++){
            Card card = deck.getCards().get(i);          
            cardButtons.get(i).putClientProperty(TEXT_CARD_PROP, card); 
            cardButtons.get(i).setIcon(card.getFaceup()?(ImageIcon)card.getImage():(ImageIcon)Card.getBackImage());
        }        
    }
    private static void equalGame(){
        attempts = 0;
        
        //all cards face up first
        allFaceup(true); 
        
        JOptionPane.showMessageDialog(null,"You have "+SLEEPING_TIME+" seconds to memorize",TEXT_TITLE,JOptionPane.WARNING_MESSAGE);
        
        //disable main window
        window.setEnabled(false);

        try {
            Thread.sleep(SLEEPING_TIME*1000); //hold for SLEEPING_TIME second.
        } catch(InterruptedException ex) {
            Thread.currentThread().interrupt();
        }  
        
        allFaceup(false); 

        //choose a random card to face up 
        JButton  btnCard = cardButtons.get( (int)Math.floor(cardButtons.size()*Math.random()));
        openCard = (Card)btnCard.getClientProperty(TEXT_CARD_PROP);
        flipCard(btnCard);        
                
        window.setEnabled(true);
        

    }
    private static void allFaceup(boolean faceup){

        cardButtons.stream().forEach((btnCard) -> {
            Card card = (Card)btnCard.getClientProperty(TEXT_CARD_PROP);
            if (card.getFaceup() != faceup) { 
                flipCard(btnCard);
            }
        });    
    }
            
            
}
