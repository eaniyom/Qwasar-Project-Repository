import requests
from bs4 import BeautifulSoup

def request_github_trending(url): #This is used to request the most trending url on git hub
    return requests.get(url) # this returns the url

def extract(page): # This function is for extraction of the requested page
    soup = BeautifulSoup(page.text, 'html.parser') #using soup as an extractor
    return soup.find_all('article') #return the result using BeautifulSoup
def transform(repos_html): #for data transformation
    result=[] # create array for storing data
    for r in repos_html: #iteration
        number_of_stars = ''.join(r.select_one('span.float-sm-right').text.split())
        repository_name = ''.join(r.select_one('h1').text.split())
        try:
            developer_name = r.select_one('img.avatar.mb-1.avatar-user')['alt']
        except(AttributeError,TypeError):
            'None name'
        result.append({'developer': developer_name, 'repository_name': repository_name, 'nbr_stars': number_of_stars})
    return result


def format(repositories_data):
    columns = ['Developer, Repository_ame, Number of Stars']
    for repository in repositories_data:
        r = [repository['developer'], repository['repository_name'], repository['nbr_stars']]
        columns.append(','.join(r))
    return '\n'.join(columns) 
def _run():
    url = 'https://github.com/trending'
    page = request_github_trending(url)
    repos_html = extract(page)
    repositories_data = transform(repos_html)
    print(format(repositories_data))
#_run()