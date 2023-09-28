# Create the csv parser
# write a function for the filter of the genre of the data

import csv

def movie_filter(genre):
    filename = "imdb-movie-data.csv"
    result = []

    with open(filename) as csvfile:
        csv_content = csv.DictReader(csvfile)

        for movie in csv_content:
            genres = movie['Genre'].split(',')
            if genre in genres:
                result.append(movie)
                
    return (result)

print(len(movie_filter('Western')))