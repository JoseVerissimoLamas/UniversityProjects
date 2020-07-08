package ucBusca.meta1;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import ucBusca.myObjects.UrlObject;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.Queue;


/**
 *  Thread responsável pela pesquisa do Url introduzido
 *  e indexação das suas palavras palavaras
 */
class AddUrl extends WebCrawler implements Runnable{
    ConcurrentHashMap<String, ArrayList<UrlObject>> wList = null;
    ConcurrentHashMap<String, ArrayList<String>> uList = null;
    ConcurrentHashMap<String, Integer> nLinks = null;
    String ws;

    /**
     * Construtor da class onde são passados
     * os parametros a serem usados
     *
     * @param ws Web Site a ser indexado
     * @param wL HashMap onde serão indexadas as
     *           palavras do web site a ser indexado
     * @param uL HashMap onde irão ser indexados
     *           os Urls que têm ligação para o
     *           url a ser indexado
     * @param nL HashMap onde serão indexados o número de
     *           links que o Url a ser indexado contém
     */
    AddUrl(String ws, ConcurrentHashMap<String, ArrayList<UrlObject>> wL, ConcurrentHashMap<String, ArrayList<String>> uL, ConcurrentHashMap<String, Integer> nL){
        this.ws= ws;
        wList = wL;
        uList = uL;
        nLinks = nL;
    }

    /**
     *  Função que a thread irá executar:
     *  Cria uma Queue de Urls a serem indexados
     *  Enquanto houver urls na queue, indexa o
     *  url no topo da queue
     */
    @Override
    public synchronized void run() {
        Queue<String> urlQ = new PriorityQueue<String>();
        urlQ.add(this.ws);
        while(!urlQ.isEmpty()){
            addURL(urlQ, urlQ.poll(), wList, uList, nLinks);
        }
    }

    /* Adiciona um URL e todos os URLs que a pagina contem */

    /**
     *  Função que indexará o web site inputed e
     *  todas as suas informações adicionais
     *  (parent urls e número de links que este contém)
     *
     * @param urlQ Queue de urls a serem indexados
     * @param ws Web site a ser indexado
     * @param wordList HashMap onde serão indexadas
     *                 as palavras
     * @param urlList HashMap onde serão indexados os
     *                parent urls
     * @param nLinks HashMap onde será indexado o
     *               número de links que o web site
     *               a ser indexado contém
     */
    protected synchronized void addURL(Queue urlQ, String ws,
                                       ConcurrentHashMap<String, ArrayList<UrlObject>> wordList,
                                       ConcurrentHashMap<String, ArrayList<String>> urlList,
                                       ConcurrentHashMap<String, Integer> nLinks){
        try {
            // Garante que começa com 'http://'
            if (! ws.startsWith("http://") && ! ws.startsWith("https://"))
                ws = "http://".concat(ws);

            // Attempt to connect and get the document
            Document doc = Jsoup.connect(ws).get();  // Documentation: https://jsoup.org/

            // Get all links
            Elements links = doc.select("a[href]");
            nLinks.put(ws, links.size());
            for (Element link : links) {
                // ignora bookmarks
                if (link.attr("href").startsWith("#")) {
                    continue;
                }
                // ignora links locais
                if (!link.attr("href").startsWith("http")) {
                    continue;
                }

                // Adiciona o Link
                if(!urlList.containsKey(link.attr("href"))){
                    // System.out.println(link.attr("href"));
                    urlList.put(link.attr("href"), new ArrayList<String>());
                    urlList.get(link.attr("href")).add(ws);
                    urlQ.add(link.attr("href"));
                }else{
                    urlList.get(link.attr("href")).add(ws);
                }
            }

            // Recebe o texto e as palavras do web site
            String text = doc.text();

            // Adiciona as palavras à HM e atribui-lhe os Links das paginas que os contêm
            String title = ws;
            if(doc.title()!=null) title = doc.title();

            String description = "No description...";
            if ( doc.text().length() > 100){
                description = doc.text().substring(0, 100);
            }else description = doc.text();
            UrlObject newUrl = new UrlObject(ws, title, description);

            addWords(text, newUrl, wordList);

        } catch (Exception e) {
            System.out.println("[ERROR] AddUrl.AddUrl");
            //e.printStackTrace();
        }
    }


    /* Adiciona as palavras a HM */

    /**
     *
     * @param text Texto do web site
     * @param ws Web site do qual as palavras vão ser
     *           indexadas
     * @param wordList HashMap onde as palavras
     *                 irão ser indexadas
     */
    private synchronized void addWords(String text, UrlObject ws, ConcurrentHashMap<String, ArrayList<UrlObject>> wordList) {

        BufferedReader reader = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(text.getBytes(StandardCharsets.UTF_8))));
        String line;

        // Vai buscar as palavras para indexar
        while (true) {
            try {
                if ((line = reader.readLine()) == null)
                    break;
                String[] words = line.split("[ ,;:.?!“”(){}\\[\\]<>']+");
                for (String word : words) {
                    word = word.toLowerCase();
                    if ("".equals(word)) {
                        continue;
                    }

                    //Verifica se a palavra já esta na HashMap
                    //Se nao tiver, adiciona-a e atribui-lhe o website
                    if(!wordList.containsKey(word)){
                        wordList.put(word, new ArrayList<UrlObject>());
                        wordList.get(word).add(ws);
                    }
                    //Se tiver a palavra mas nao o website, atribui-lhe o ws
                    else{
                        if(!wordList.get(word).contains(ws)){
                            wordList.get(word).add(ws);
                        }
                    }

                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // Close reader
        try {
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}