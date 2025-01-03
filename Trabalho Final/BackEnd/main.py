import pandas as pd
import numpy as np
import requests
import time
from sklearn.metrics.pairwise import cosine_similarity
from fastapi import FastAPI, HTTPException, Body
from fastapi.middleware.cors import CORSMiddleware


def similarity(row1,row2,weights):
    similarity = 0
    for attribute, weight in weights.items():
        similarity += weight * cosine_similarity(np.array(row1[attribute]).reshape(1,-1), np.array(row2[attribute]).reshape(1,-1) )[0,0]
    return similarity


def recom(sample,df,weight):
    df["similarity"] = df.apply(lambda row: similarity(row1=row, row2=sample,weights=weight), axis=1)
    df = df.sort_values(by=['similarity'],ascending=False)
    ans = df['mal_id'].iloc[:5].tolist()
    return ans


def treatSymptons(sympthons):
    sympthons = sympthons.replace(" ","")
    sympthons = sympthons.replace(")","")
    sympthons = sympthons.replace("(","")

    res =[]
    sympthons = sympthons.split(",")


    for symp in sympthons:
        aux = []
        if(symp[0]=='!'):
            aux.append(0)
        else:
            aux.append(1)

        
        splitpos =symp.find(":")
        aux.append(int (symp[symp.find("\"")+1:splitpos]))
        aux.append(int (symp[splitpos+1:symp.find("\"",splitpos)]) )
        res.append(aux)
     
    return res

def getSample(rules,weight,answerns):

    sample = {
        "episodes": [0],
        "airing": [0],
        "duration": [0],
        "rank": [0],
        "score": [0],
        "year": [0],
        "Action": [0],
        "Adventure": [0],
        "Award Winning": [0],
        "Comedy": [0],
        "Drama": [0],
        "Fantasy": [0],
        "Horror": [0],
        "Mystery": [0],
        "Romance": [0],
        "Sci-Fi": [0],
        "Slice of Life": [0],
        "Sports": [0],
        "Supernatural": [0],
        "Suspense": [0],
        "Shounen": [0],
        "Seinen": [0],
        "Josei": [0]
    }  
        
    for rule in rules:
        cause, sympthons, val = rule.split(";")
        sympthons = treatSymptons(sympthons)

        aprove = True

        print(f"cause: {cause}")
        print(f"sympthons: {sympthons}")
        print(f"val: {val}\n")
        for symp in sympthons:
            if(symp[0]==1):
                if(answerns[symp[1]]!=symp[2]):
                    aprove=False
            else:   
                if(answerns[symp[1]]==symp[2]):
                    aprove=False

        if(aprove):
            attrName = cause[cause.find("\"")+1:cause.find(":")]
            auxVal = cause[cause.find(":")+1: cause.find("\"",cause.find(":"))]
            weight[attrName]= float(val)
            sample[attrName]= int(auxVal)
    print(f"samples: {sample}\n")
    print(f"weights: {weight}\n")
    return sample
    

df = pd.read_csv("../Data Extraction/result.csv")
app = FastAPI()
app.df = df
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
app.weights = {
    "episodes": 0,
    "airing": 0,
    "duration": 0,
    "rank": 0,
    "score": 0,
    "year": 0,
    "Action": 0,
    "Adventure": 0,
    "Award Winning": 0,
    "Comedy": 0,
    "Drama": 0,
    "Fantasy": 0,
    "Horror": 0,
    "Mystery": 0,
    "Romance": 0,
    "Sci-Fi": 0,
    "Slice of Life": 0,
    "Sports": 0,
    "Supernatural": 0,
    "Suspense": 0,
    "Shounen": 0,
    "Seinen": 0,
    "Josei": 0
}   

app.rules = open("./rules.txt").read().splitlines()


@app.post('/')
async def recommend(params = Body(...)):
    tentativas = 5
    i = 0
    while i <= tentativas:
        try:   
            sample = getSample(app.rules,app.weights,params['body'])
            print("reached\n")
            ans = recom(sample,app.df,app.weights)
            print("reached\n")
            return ans
        except requests.exceptions.HTTPError as e:
            if e.response.status_code == 429:
                tempo_espero = 2 ** i
                time.sleep(tempo_espero)
                i += 1
        except Exception as e:
            raise HTTPException(status_code=400, detail=str(e))
    
            