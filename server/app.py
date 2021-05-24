import os
import re
from flask import Flask, render_template, request
import redis


redis_client = redis.StrictRedis(host=os.environ.get('REDIS_HOST'), port=6379, db=0)
char_limit = 15


def get_banned_words(file_path='banned.txt'):
    """Returns the list of banned words"""
    if os.path.exists(file_path):
        with open(file_path, 'r') as file:
            lines = file.readlines()
        return [x.strip().lower() for x in lines]
    return []


def schedule_word(req):
    """Schedules the word"""
    word = req.values.get('word', '').replace(" ", "").lower()
    regex = re.compile('[^a-z]')
    word = regex.sub('', word)
    if not word:
        return False
    if word not in banned_list:
        word = word[:char_limit-1]
        redis_client.lpush('word_list', word)
    return True


app = Flask(__name__)
banned_list = get_banned_words()


@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        if schedule_word(request):
            return render_template("index.html", message='Message sent')
        return render_template("index.html", message='Error')
    else:
        context = {
            'char_limit': char_limit
        }
        return render_template("index.html", **context)


@app.route('/next/')
def get_next_word():
    if request.args.get('key') == os.environ.get('SERVER_KEY', 'replace'):
        if redis_client.llen('word_list') > 0:
            word = redis_client.rpop('word_list')
            if word in banned_list:
                return ''
            return word
    return ''


if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0')
