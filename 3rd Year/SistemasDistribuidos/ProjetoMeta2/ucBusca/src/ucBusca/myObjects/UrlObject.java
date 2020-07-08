package ucBusca.myObjects;

import java.io.Serializable;

public class UrlObject implements Serializable {
    protected String url;
    protected String Title;
    protected String Description;
    protected String lang;

    public UrlObject(String url2, String ot, String od){
        url = url2;
        Title = ot;
        Description = od;
    }

    public void setUrl(String url){
        this.url = url;
    }

    public void setTitle(String title){
        this.Title = title;
    }

    public void setDescription(String description){
        this.Description = description;
    }

    public String getUrl(){
        return url;
    }

    public String getTitle(){
        return Title;
    }

    public String getDescription(){
        return Description;
    }

    public String toString(){
        return this.url;
    }
}
