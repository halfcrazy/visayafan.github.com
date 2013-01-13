function hideShowArticles(categoryName) {
    var articlesUl = document.getElementById(categoryName);
    
    if (articlesUl.style.display == "none")
	articlesUl.style.display = "";
    else
	articlesUl.style.display = "none";
}