package ucBusca.meta1;

import java.io.*;
import java.util.ArrayList;

import ucBusca.myObjects.UrlObject;

import java.util.concurrent.ConcurrentHashMap;

/**
 *  Class onde irá ser guardado:
 *   > a HashMap que indexa às palavras os links que
 *  a contêm,
 *   > a HashMap que terá indexado os links que têm
 *  ligação para o Link (key)
 *   > a HashMap que tem indexado o numero de links
 *  que o link contém
 */
public class WebCrawler{

    // Cria a hashmap onde vao ser guardadas as palavrs e os seus linsk
    // É usado o ConcurrentHashMap visto que este é mais seguro nas syncros

    public ConcurrentHashMap<String, ArrayList<UrlObject>> wordList = new ConcurrentHashMap<>();
    public ConcurrentHashMap<String, ArrayList<String>> urlList = new ConcurrentHashMap<>();
    public ConcurrentHashMap<String, Integer> numbLinks = new ConcurrentHashMap<>();


    /**
     *  Lê e guarda a informação contida nos ficheiros de texto
     */
    WebCrawler(){
        readFiles();
        for (String key:wordList.keySet()){
            System.out.println(key+" : "+wordList.get(key));
        }
    }

    public void readFiles(){
        try {
            ObjectInputStream ow = new ObjectInputStream(new FileInputStream(new File("wordLinks")));
            wordList= (ConcurrentHashMap<String, ArrayList<UrlObject>>) ow.readObject();
            ow.close();
            ow = new ObjectInputStream(new FileInputStream(new File("urlList")));
            urlList = (ConcurrentHashMap<String, ArrayList<String>>) ow.readObject();
            ow.close();
            ow = new ObjectInputStream(new FileInputStream(new File("numbLinks")));
            numbLinks= (ConcurrentHashMap<String, Integer>) ow.readObject();
            ow.close();

        }catch (FileNotFoundException e) {
            File f = new File("wordLinks");
            f= new File("urlList");
            f=new File("numbLinks");
        }catch (IOException e) {
            System.out.println("[Empty File]");
            //e.printStackTrace();
        }catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     *  Pesquisa a(s) palavra(s) na HM e retorna a ArrayList dos
     *  Links onde esta(s) aparece
     *
     * @param wList HashMap que contém a indexação das palavras
     * @param search Palavra que será pesquisada
     * @param sorted Boolean de controlo se o ArrayList dos Urls
     *               será organizado por número de links que
     *               este contém ou não
     * @return ArrayList que contém os Urls onde a palavra aparece
     */
    public ArrayList<UrlObject> searchURLs(ConcurrentHashMap<String, ArrayList<UrlObject>> wList, String search, boolean sorted){
        ConcurrentHashMap<String, ArrayList<UrlObject>> aux = wList;

        /* Caso a pesquisa contenha varias palavras */
        if(search.split("[ ,;:.?!“”(){}\\[\\]<>']+").length >= 2){
            boolean presentes = true;

            // Ve se todas as palavras estao na HM
            for(int i=0; i<search.split("[ ,;:.?!“”(){}\\[\\]<>']+").length; i++){
                if(!aux.containsKey(search.split("[ ,;:.?!“”(){}\\[\\]<>']+")[i])){
                    presentes = false;
                    break;
                }
            }
            if(presentes){
                ArrayList<UrlObject> sharedLinks = new ArrayList<>(); // AL auxiliar que ira conter os URLs em comum

                // Faz a copia dos URLs todos de uma das palavras
                sharedLinks.addAll(aux.get(search.split("[ ,;:.?!“”(){}\\[\\]<>']+")[0]));

                // Usa o ' restainAll() ' para apagar os URLs que NAO sao communs entre a AL auxiliar e a AL dos
                // URLs que as proximas palavras têm
                for(int i=1; i<search.split("[ ,;:.?!“”(){}\\[\\]<>']+").length; i++){
                    sharedLinks.retainAll(aux.get(search.split("[ ,;:.?!“”(){}\\[\\]<>']+")[i]));
                }

                // Display dos URLs em comum (ordenados[sorted==true] ou nao[sorted==false])
                if(sorted){
                    return displayOrdenado(sharedLinks);
                }else{
                    return sharedLinks;
                }
            }else{
                System.out.println("Nothing found");
                return null;
            }
        }
        /* Caso a pesquisa contena so uma palavra */
        else{
            if(aux.containsKey(search)){
                if(sorted){
                    return displayOrdenado(aux.get(search));
                }else{
                    return aux.get(search);
                }
            }else{
                System.out.println("Nothing found");
                return null;
            }
        }
    }


    /**
     *  Função auxiliar da searchURLs() que irá ordenar os urls
     *  por número de links que estes contêm
     *
     * @param urls ArrayList por organizar
     * @return ArrayList organizado
     */
    private ArrayList<UrlObject> displayOrdenado(ArrayList<UrlObject> urls){
        ArrayList<UrlObject> urlsSorted = new ArrayList<>(); // Onde vao estar os URLs oredenados

        for(UrlObject url : urls){
            if(!urlsSorted.isEmpty()){ // Caso geral
                boolean adicionado = false; // Controlo para saber se o url foi adicionado
                for(int i = 0; i < urlsSorted.size(); i++){ // (Pelo menos um URL ja la esta)
                    // Se tiver mais Links, será colocado 1o na AL
                    if( getNumbLinks(urlsSorted.get(i).getUrl()) < getNumbLinks(url.getUrl()) && !adicionado ){
                        urlsSorted.add(i, url);
                        adicionado = true;
                    }
                    if(i==10){
                        break;
                    }
                } if(!adicionado) urlsSorted.add(url); // Caso este url seja o que tem nos links, é inserido em ultimo

            }else{ // Caso para o 1o elemento
                urlsSorted.add(url);
            }
        }

        return urlsSorted;
    }

    private Integer getNumbLinks(String url){
        if(numbLinks.containsKey(url)) return numbLinks.get(url);
        return 0;
    }

    /**
     *  Função que retornará a ArrayList de urls que contêm
     *  link para o url inputed
     *
     * @param url Url inputed
     * @param urlList HashMap que contém a informação de quantos
     *                links tem o Url inputed
     * @return ArrayList dos Urls que contêm o Url inputed
     */
    public ArrayList<String> parentUrl(String url, ConcurrentHashMap<String, ArrayList<String>> urlList){
        //ArrayList<String> parentUrls = null;
        if(urlList.containsKey("http://"+url)){
            return urlList.get("http://"+url);
        }
        else if(urlList.containsKey("https://"+url)){
            return urlList.get("https://"+url);
        }
        else{
            return null;
        }
    }

}