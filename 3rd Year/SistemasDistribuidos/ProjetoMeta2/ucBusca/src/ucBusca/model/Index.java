package ucBusca.model;

import ucBusca.meta1.RMIInterface;

public class Index {
    private String link;
    private String answerMsg = "Could not index";

    public void setLink(String link) {
        this.link = link;
    }
    public String getLink(){
        return link;
    }

    public void setAnswerMsg(String answerMsg){
        this.answerMsg = answerMsg;
    }

    public String getAnswerMsg(){
        return this.answerMsg;
    }

}