require 'socket'
#http://www.ruby-doc.org/stdlib-1.9.3/libdoc/socket/rdoc/Socket.html
def Menu()
    puts("1 - Cadastrar novo site:")
    puts("2 - Buscar site: ")
    puts("3 - Sair: ")
    opcao = gets.chomp
end

def Cadastrar()
    echo("clear")
    puts("Insira o nome do site: ")
    nomeSite = gets.chomp
    puts("Insira o endereco do site: ")
    link = gets.chomp
    puts("Tags relacionadas ao site: (Insira as Tags separadas por virgula) ")
    tags = gets.chomp
end

def Buscar()
    puts("Insira uma palavra-chave para busca: ")
    
