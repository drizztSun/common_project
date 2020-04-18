from fastapi import FastAPI

app = FastAPI()

# uvicorn main:app --reload
# start this service

@app.get("/")
async def root():
    return {'message': "Hello world"}
