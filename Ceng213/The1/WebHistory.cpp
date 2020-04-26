#include "WebHistory.hpp"

WebHistory::WebHistory()
{
    
}

WebHistory::WebHistory(std::string historyText)
{
	
    
    std::string delimiter = " | ";

	std::string tabInfo;
    std::string url;
    std::string timestamp;
    size_t pos = 0;

    while (true)
	{
        pos = historyText.find(delimiter);

        bool breakTheLoop = (pos == std::string::npos);

        tabInfo = historyText.substr(0, pos);
        historyText.erase(0, pos + delimiter.length());

        pos = tabInfo.find(" ");
        
        url = tabInfo.substr(0, pos);
        timestamp = tabInfo.substr(pos + 1, tabInfo.length() - pos);

		Node<Tab> *newPage = new Node<Tab>(Tab(url, std::atoi(timestamp.c_str())), NULL, NULL);
        insertInOrder(newPage);

        if (breakTheLoop)
		{
			break;
		}
    }
}

void WebHistory::printHistory()
{
	std::cout << "Your web history:" << std::endl;
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;
	if (history.getHead()->next == history.getTail())
	{
		std::cout << "History is empty." << std::endl;
		std::cout << std::endl;
	}
	else
	{
		Node<Tab> *node = history.getFirstNode();
		
		while (node != history.getTail())
		{
		    std::cout << "Page: " << node->element.getUrl() << std::endl;
			std::cout << "Last Visited: " << node->element.getTimestamp() << std::endl;
			std::cout << std::endl;
		    node = node->next;
		}
	}
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << std::endl;
}

WebHistory::WebHistory(std::string url, int timestamp)
{
	
	Node<Tab>* newtab = new Node<Tab>;

	
    Node<Tab>* hist_head = history.getHead();
    Node<Tab>* hist_tail = history.getTail();

     
    (newtab->element).setUrl(url);

    
    (newtab->element).setTimestamp(timestamp);

     
    newtab->next = hist_tail;
    newtab->prev = hist_head;

    hist_head->next = newtab;
    hist_tail->prev = newtab; 


}

WebHistory::~WebHistory()
{
	

}

void WebHistory::insertInOrder(Node<Tab> *newPage)
{
	

    
    Node<Tab>* hist_head = history.getHead();
    Node<Tab>* hist_tail = history.getTail();

    Node<Tab>* current = hist_head->next;
    
    
    if(current == hist_tail){
       
       hist_head->next = newPage;
       hist_tail->prev = newPage;

       newPage->prev = hist_head;
       newPage->next = hist_tail;

    }else{
 
    
    while(current != hist_tail && (newPage->element.getTimestamp())<(current->element.getTimestamp()))
    	current = current->next;



    newPage->prev = current->prev;
    newPage->next = current;

    current->prev->next = newPage;
    current->prev = newPage;
}
}

void WebHistory::goToPage(std::string url, int timestamp)
{
	
	Node<Tab> *newtab = new Node<Tab>;
	newtab->element.setUrl(url);
	newtab->element.setTimestamp(timestamp);

	this->insertInOrder(newtab);
}

void WebHistory::clearHistory()
{
	
    
    Node<Tab>* hist_head = history.getHead();
    Node<Tab>* hist_tail = history.getTail();

	Node<Tab>* current = hist_head->next;
	Node<Tab>* tmp ;

	while(current != hist_tail){
      tmp = current;
      current = current->next;
      delete tmp;
	}

	hist_head->next = hist_tail;
	hist_tail->prev = hist_head;
}

void WebHistory::clearHistory(int timestamp)
{
	
    
    Node<Tab>* hist_head = history.getHead();
    Node<Tab>* hist_tail = history.getTail();

    Node<Tab>* startpoint = hist_head->next;

    while(startpoint != hist_tail && (timestamp)<(startpoint->element.getTimestamp()))
    	startpoint = startpoint->next;
    
    
    if(startpoint == hist_tail)
    	return;
    else if(startpoint == hist_head->next){
    	
        this->clearHistory();
    }else{

    Node<Tab>* current = startpoint;
	Node<Tab>* tmp ;
	Node<Tab>* prev_node = startpoint->prev;

	while(current != hist_tail){
      tmp = current;
      current = current->next;
      delete tmp;
	}

	prev_node->next = hist_tail;
	hist_tail->prev = prev_node;

    }

}

WebHistory WebHistory::operator+(const WebHistory &rhs) const
{
	

    
    Node<Tab>* hist_head = history.getHead();
    Node<Tab>* hist_tail = history.getTail();
    Node<Tab>* rhs_head = (rhs.history).getHead();
    Node<Tab>* rhs_tail = (rhs.history).getTail();


    WebHistory newHist;
    
    Node<Tab>* current = hist_head->next;
    Node<Tab>* current_rhs = rhs_head->next;
    
    
    while(current != hist_tail){
        Node<Tab> *newnode = new Node<Tab>;
        newnode->element = current->element;
    	newHist.insertInOrder(newnode);
    	current = current->next;
    }

    
    while(current_rhs != rhs_tail){
        Node<Tab> *newnode = new Node<Tab>;
        newnode->element = current_rhs->element;
    	newHist.insertInOrder(newnode);
    	current_rhs = current_rhs->next;
    }

    return newHist;

}

int WebHistory::timesVisited(std::string pageName)
{
	
    
    Node<Tab>* hist_head = history.getHead();
    Node<Tab>* hist_tail = history.getTail();

	int i = 0;
	Node<Tab>* current = hist_head->next;
	while(current != hist_tail){
		if((current->element).getWebSite() == pageName)
			i++;
		current = current->next;
	}

	return i;

}

std::string WebHistory::mostVisited()
{
	
	
    Node<Tab>* hist_head = history.getHead();
    Node<Tab>* hist_tail = history.getTail();


	std::string mostvisited;
	int visit = 0;
    
    Node<Tab>* current = hist_head->next;
    
    if(hist_head->next == hist_tail)
        return "";

    while(current != hist_tail){
    	int tmp_visit = this->timesVisited((current->element).getWebSite());
		if(tmp_visit>visit){
			mostvisited = (current->element).getWebSite();
		    visit = tmp_visit;
		}


		current = current->next;
	}
  
  return mostvisited;

}