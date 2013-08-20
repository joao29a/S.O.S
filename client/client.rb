require 'socket'


def Menu()
    puts("1 - Cadastrar novo site:")
    puts("2 - Buscar site: ")
    puts("3 - Sair: ")
    opcao = gets.chomp
    if (opcao == "1")
        Cadastrar()
    elsif (opcao == "2")
        Buscar()
    else
        puts("Adios!")
    end
end

def Cadastrar()
    system "clear"
    socket = TCPSocket.new 'localhost', 8888
    puts("Insira o nome do site: ")
    nomeSite = socket.gets.chomp
    puts("Insira o endereco do site: ")
    link = socket.gets.chomp
    puts("Tags relacionadas ao site: (Insira as Tags separadas por virgula) ")
    tags = socket.gets.chomp
end

#def Buscar()
#    puts("Insira uma palavra-chave para busca: ")


Menu()

