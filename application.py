import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    # """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM port WHERE id = :user_id", user_id=session.get("user_id"))
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session.get("user_id"))
    s = cash[0]['cash']
    for stock in stocks:
        s += stock['price'] * stock['share']
    return render_template("index.html", stocks=stocks, cash=cash, s=s)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        company = request.form.get("company")
        if not lookup(company):
            return apology("The company you requested doesn't exist", 403)
        com = lookup(company)['price']
        amount = round(float(request.form.get("amount")))
        price = com * int(amount)
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session.get("user_id"))
        cash = cash[0]['cash']
        if cash < price:
            return apology("Sorry you do not have enough money to buy this share(s)", 403)
        date = datetime.now()
        temp = cash - price
        time = f'{date.year}/{date.month}/{date.day} {date.hour}:{date.minute}:{date.second}'
        db.execute("INSERT INTO stocks (id, symbol, shares, price, total_price, timestamp) VALUES(:user_id, :symbol, :shares, :price, :total_price, :timestamp)"
        , user_id=session.get('user_id'), symbol=company, shares=amount, price=com, total_price=price, timestamp=time)
        port = db.execute("SELECT share FROM port WHERE id = :user_id AND symbol = :symbol", user_id=session.get('user_id'), symbol=company)
        if not port:
            db.execute("INSERT INTO port (id, symbol, name, price, share) VALUES (:user_id, :symbol, :name, :price, :total)",user_id=session.get('user_id'), symbol=company, name=lookup(company)['name'], price=com, total=amount)
        else:
            shares = port[0]['share']
            s = int(shares) + int(amount)
            db.execute("UPDATE port SET share = :share,price = :price WHERE id = :user_id AND symbol = :symbol", share=s, user_id=session.get('user_id'), symbol=company, price=com)
        db.execute("UPDATE users SET cash = :temp WHERE id = :user_id", temp=temp, user_id=session.get("user_id"))
        return redirect('/')
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM stocks WHERE id = :user_id", user_id=session.get("user_id"))
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        company = lookup(request.form.get("company"))
        if not company:
            return apology("Sorry the symbol you requested wasn't found", 403)
        companies = []
        companies.append(f"A share of {company['name']}({company['symbol']}) costs {company['price']}.")
        return render_template("quoted.html", companies=companies)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        # Ensure password verifier was submitted
        elif not request.form.get("password_verify"):
            return apology("must provide password again", 403)
        elif request.form.get("password") != request.form.get("password_verify"):
            return apology("password and password-verifier must be the same", 403)

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        # Ensuring username does not exist
        if rows:
            return apology("username is already taken", 403)

        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash_password)", username=request.form.get("username"), hash_password=generate_password_hash(
            request.form.get("password")))

        return redirect("/login", code=307)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        company = request.form.get("company")
        print(company)
        com = lookup(company)['price']
        amount = round(float(request.form.get("amount")))
        price = com * int(amount)
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session.get("user_id"))
        cash = cash[0]['cash']
        date = datetime.now()
        time = f'{date.year}/{date.month}/{date.day} {date.hour}:{date.minute}:{date.second}'
        port = db.execute("SELECT share FROM port WHERE id = :user_id AND symbol = :symbol", user_id=session.get('user_id'), symbol=company)
        shares = port[0]['share']
        if int(amount) > shares:
            return apology("You are trying to sell more shares than you own", 403)
        db.execute("INSERT INTO stocks (id, symbol, shares, price, total_price, timestamp) VALUES(:user_id, :symbol, :shares, :price, :total_price, :timestamp)"
        , user_id=session.get('user_id'), symbol=company, shares= -1 * int(amount), price=com, total_price=price, timestamp=time)
        s = int(shares) - int(amount)
        if s == 0:
            db.execute("DELETE FROM port WHERE id = :user_id AND symbol = :symbol", user_id=session.get('user_id'), symbol=company)
        else:
            db.execute("UPDATE port SET share = :share, price = :price WHERE id = :user_id AND symbol = :symbol", share=s, user_id=session.get('user_id'), symbol=company, price=com)
        db.execute("UPDATE users SET cash = :temp WHERE id = :user_id", temp=cash + price, user_id=session.get("user_id"))
        return redirect('/')
    else:
        stocks = db.execute("SELECT symbol FROM port WHERE id = :user_id", user_id=session.get("user_id"))
        sym = []
        for i in stocks:
            sym.append(i['symbol'])
        return render_template("sell.html", sym=sym)

@app.route("/cash", methods=["GET", "POST"])
def cash():
    if request.method == "POST":
        cash = float(request.form.get("cash"))
        temp = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session.get("user_id"))
        temp = temp[0]['cash']
        db.execute("UPDATE users SET cash = :c WHERE id = :user_id", c=cash + temp, user_id=session.get("user_id"))
        date = datetime.now()
        time = f'{date.year}/{date.month}/{date.day} {date.hour}:{date.minute}:{date.second}'
        db.execute("INSERT INTO stocks (id, symbol, price, timestamp) VALUES (:user_id, :symbol, :price, :timestamp)", symbol="CASH", price=cash, timestamp=time, user_id=session.get("user_id"))
        return redirect("/")
    else:
        return render_template("cash.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
