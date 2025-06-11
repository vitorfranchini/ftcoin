# ⚙️ Configuração do MariaDB C++ Connector no Visual Studio (64-bit)

Para que o projeto **ftcoin** funcione corretamente com o banco de dados MariaDB, é necessário configurar o **MariaDB C++ Connector** no Visual Studio.

## 📥 Pré-requisitos

- Baixe e instale o **MariaDB C++ Connector 64-bit**  
  🔗 [https://mariadb.com/kb/en/mariadb-connector-cpp/](https://mariadb.com/kb/en/mariadb-connector-cpp/)

## 🛠️ Etapas de configuração no Visual Studio

### 1. Include Directories
Adicione o caminho para os arquivos de cabeçalho `.hpp`:


### 2. Library Directories
Adicione o caminho para os arquivos de biblioteca `.lib`:


### 3. Additional Dependencies
Inclua o nome da biblioteca a ser linkada:


## ✅ Exemplo completo

| Configuração              | Caminho / Valor                                                                 |
|---------------------------|----------------------------------------------------------------------------------|
| Include Directories       | `C:\libs\MariaDB C++ Connector 64-bit\include`                                  |
| Library Directories       | `C:\libs\MariaDB C++ Connector 64-bit\libs`                                     |
| Additional Dependencies   | `mariadbclient.lib`                                                             |

## 📌 Observações

- Use o **Visual Studio 64-bit**, compatível com a biblioteca.
- Certifique-se de que as **DLLs necessárias** estejam acessíveis na pasta do executável ou configure o `PATH`.

---

