package ucBusca.meta1;

import ucBusca.myObjects.UrlObject;

import java.io.*;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentHashMap;

/**
 *  Thread responsável por guardar as HashMaps nos ficheiros
 */
class FileSaver extends WebCrawler implements Runnable{

    private ConcurrentHashMap<String, ArrayList<UrlObject>> wList;
    private ConcurrentHashMap<String, ArrayList<String>> uList;
    private ConcurrentHashMap<String, Integer> nLinks;

    /**
     *
     * @param wL HashMap onde estão indexadas as palavras
     * @param uL Hashmap onde estão indexados os urls parents
     * @param nL Hashmap onde está indexado o número links
     */
    FileSaver(ConcurrentHashMap<String, ArrayList<UrlObject>> wL, ConcurrentHashMap<String, ArrayList<String>> uL, ConcurrentHashMap<String, Integer> nL){
        wList = wL;
        uList = uL;
        nLinks = nL;
    }


    /**
     *  Função que a thread vai correr:
     *  Vai dar load da informação dos ficheiros e
     *  vai guardar a informação das Hashmaps
     */
    @Override
    public synchronized void run() {

        while(!Thread.currentThread().isInterrupted()) {
            try {

                //loadHM(wList, uList, nLinks);
                saveHM(wList, uList, nLinks);
                Thread.sleep(10000);

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }


    /**
     *  Função que vai buscar a informação dos ficheiros
     *  irá comparar com a informação atual das HashMaps
     *  e irá acrescentar o que estas não têm para poder
     *  evitar apagar informações que o ficheiro contenha
     *  e que as HashMaps não contenham
     *
     * @param wordList HashMap onde estão indexadas as palavras
     * @param urlList Hashmap onde estão indexados os urls parents
     * @param nLinks Hashmap onde está indexado o número links
     */
    private void loadHM(ConcurrentHashMap<String, ArrayList<UrlObject>> wordList, ConcurrentHashMap<String, ArrayList<String>> urlList, ConcurrentHashMap<String, Integer> nLinks){
        ConcurrentHashMap<String, ArrayList<UrlObject>> wordListAux;
        ConcurrentHashMap<String, ArrayList<String>> urlListAux;
        ConcurrentHashMap<String, Integer> nLinksAux;

        FileInputStream fw = null;
        ObjectInputStream ow = null;
        FileInputStream fu = null;
        ObjectInputStream ou = null;
        FileInputStream fn = null;
        ObjectInputStream on = null;
        try {

            fw = new FileInputStream(new File("wordLinks"));
            ow = new ObjectInputStream(fw);
            fu = new FileInputStream(new File("urlList"));
            ou = new ObjectInputStream(fu);
            fn = new FileInputStream(new File("numbLinks"));
            on = new ObjectInputStream(fn);

            wordListAux = (ConcurrentHashMap<String, ArrayList<UrlObject>>) ow.readObject();

            urlListAux = (ConcurrentHashMap<String, ArrayList<String>>) ou.readObject();

            nLinksAux = (ConcurrentHashMap<String, Integer>) on.readObject();

            ow.close();
            fw.close();
            ou.close();
            fu.close();
            on.close();
            fn.close();

            for(String key : wordListAux.keySet()){
                if(!wordList.containsKey(key)){
                    wordList.put(key, wordListAux.get(key));
                } else{
                    for(UrlObject url : wordListAux.get(key)){
                        if(!wordList.get(key).contains(url)){
                            wordList.get(key).add(url);
                        }
                    }
                }
            }for(String key : urlListAux.keySet()){
                if(!urlList.containsKey(key)){
                    urlList.put(key, urlListAux.get(key));
                } else {
                    for(String url : urlListAux.get(key)){
                        if(!urlList.get(key).contains(url)){
                            urlList.get(key).add(url);
                        }
                    }
                }
            }for(String key : nLinksAux.keySet()){
                if(!nLinksAux.containsKey(key)){
                    nLinksAux.put(key, nLinksAux.get(key));
                }
            }

        }catch (FileNotFoundException e) {
            File f = new File("urlList");
            f= new File("wordList");
            f=new File("numbLinks");
        }catch (IOException e) {
            System.out.println("[Load : Empty File]");
        }catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

    }


    /**
     *  Função que vai guardar a informação das HashMaps nos
     *  ficheiros
     *
     * @param wordList HashMap onde estão indexadas as palavras
     * @param urlList Hashmap onde estão indexados os urls parents
     * @param nLinks Hashmap onde está indexado o número links
     */
    private synchronized void saveHM(ConcurrentHashMap<String, ArrayList<UrlObject>> wordList, ConcurrentHashMap<String, ArrayList<String>> urlList, ConcurrentHashMap<String, Integer> nLinks){
        try{

            ObjectOutputStream wo = new ObjectOutputStream(new FileOutputStream(new File("wordLinks")));
            ObjectOutputStream uo = new ObjectOutputStream(new FileOutputStream(new File("urlList")));
            ObjectOutputStream un = new ObjectOutputStream(new FileOutputStream(new File("numbLinks")));

            wo.writeObject(wordList);
            System.out.println("[SAVED] "+ wordList.size());
            uo.writeObject(urlList);
            un.writeObject(nLinks);

            wo.close();
            uo.close();
            un.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}