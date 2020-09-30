FROM python:3.7-alpine
WORKDIR /code
COPY server/requirements.txt .
RUN pip install -r requirements.txt
COPY server .
ENTRYPOINT [ "python" ]
CMD ["app.py"]
