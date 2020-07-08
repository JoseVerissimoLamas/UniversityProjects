package ucBusca.model;

import ucBusca.meta1.RMIInterface;
import ucBusca.myObjects.UrlObject;

import java.util.ArrayList;

public class Browser {
    private String query;
    private String message;
    private ArrayList<String> results = new ArrayList<>();
    private ArrayList<UrlObject> detailedResults = new ArrayList<>();
    private ArrayList<UrlObject> translatedResults = new ArrayList<>();
    private String lang;

    public void setQuery(String query){
        this.query = query;
    }
    public String getQuery(){
        return query;
    }

    public void setResults(ArrayList<String> results){
        this.results = results;
    }

    public ArrayList<String> getResults() {
        return results;
    }

    public void setMessage(String message){
        this.message = message;
    }
    public String getMessage(){
        return message;
    }

    public void setDetailedResults(ArrayList<UrlObject> detailedResults) {
        this.detailedResults = detailedResults;
    }
    public ArrayList<UrlObject> getDetailedResults() {
        return detailedResults;
    }

    public void setTranslatedResults(ArrayList<UrlObject> translatedResults) {
        this.translatedResults = translatedResults;
    }
    public ArrayList<UrlObject> getTranslatedResults() {
        return translatedResults;
    }

    public void setLang(String lang) {this.lang = lang;}

    public String getLang(){return lang;}
}
