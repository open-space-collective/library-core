////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Containers/Table.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Table.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

// #include <fast-cpp-csv-parser/csv.h>
#include <rapidcsv/rapidcsv.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Table::Table                                (   const   Array<String>&              aHeader,
                                                                                const   Array<Row>&                 aRowArray                                   )
                                :   header_(aHeader),
                                    rows_(aRowArray)
{

    for (auto& row : rows_)
    {

        if (row.getSize() > header_.getSize())
        {
            throw library::core::error::RuntimeError("Header size [{}] lower than maximum row size [{}].", header_.getSize(), row.getSize()) ;
        }

        row.associateTable(this) ;

    }

}

                                Table::Table                                (   const   Array<String>&              aHeader                                     )
                                :   header_(aHeader),
                                    rows_(Array<Row>::Empty())
{

}

                                Table::Table                                (   const   Table&                      aTable                                      )
                                :   header_(aTable.header_),
                                    rows_(aTable.rows_)
{

    for (auto& row : rows_)
    {
        row.associateTable(this) ;
    }

}

Table&                          Table::operator =                           (   const   Table&                      aTable                                      )
{

    if (this != &aTable)
    {

        header_ = aTable.header_ ;
        rows_ = aTable.rows_ ;

        for (auto& row : rows_)
        {
            row.associateTable(this) ;
        }
        
    }

    return *this ;

}

bool                            Table::operator ==                          (   const   Table&                      aTable                                      ) const
{
    return (header_ == aTable.header_) && (rows_ == aTable.rows_) ;
}

bool                            Table::operator !=                          (   const   Table&                      aTable                                      ) const
{
    return !((*this) == aTable) ;
}

const Row&                      Table::operator []                          (   const   Index&                      aRowIndex                                   ) const
{

    if (aRowIndex >= rows_.getSize())
    {
        throw library::core::error::RuntimeError("Row index [{}] out of range [0 - {}].", aRowIndex, rows_.getSize()) ;
    }
    
    return rows_[aRowIndex] ;

}

const Cell&                     Table::operator ()                          (   const   Index&                      aRowIndex,
                                                                                const   Index&                      aColumnIndex                                ) const
{

    if (aRowIndex >= rows_.getSize())
    {
        throw library::core::error::RuntimeError("Row index [{}] out of range [0 - {}].", aRowIndex, rows_.getSize()) ;
    }

    return rows_[aRowIndex][aColumnIndex] ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Table&                      aTable                                      )
{

    auto convertRowToStringArray = [] (const Row& aRow) -> Array<String>
    {

        Array<String> stringArray = Array<String>::Empty() ;

        stringArray.reserve(aRow.getSize()) ;

        for (const auto& cell : aRow)
        {
            stringArray.add(cell.toString(Cell::Format::JSON)) ;
        }

        return stringArray ;

    } ;

    auto formatLine = [] (const Array<String>& aStringArray) -> String
    {

        std::stringstream stringStream ;

        for (const auto& stringElement : aStringArray)
        {
            stringStream << std::left << std::setw(20) << std::setfill(' ') << stringElement << " " ;
        }

        return stringStream.str() ;

    } ;

    library::core::utils::Print::Header(anOutputStream, "Table") ;

    library::core::utils::Print::Line(anOutputStream) << "Rows:" << aTable.getRowCount() ;
    library::core::utils::Print::Line(anOutputStream) << "Columns:" << aTable.getColumnCount() ;

    library::core::utils::Print::Separator(anOutputStream) ;

    library::core::utils::Print::Line(anOutputStream) << formatLine(aTable.header_) ;

    library::core::utils::Print::Separator(anOutputStream) ;

    if (aTable.getRowCount() > 0)
    {
        library::core::utils::Print::Line(anOutputStream) << formatLine(convertRowToStringArray(aTable[0])) ;
    }

    if (aTable.getRowCount() > 1)
    {
        library::core::utils::Print::Line(anOutputStream) << formatLine(convertRowToStringArray(aTable[1])) ;
    }

    if (aTable.getRowCount() > 4)
    {
        library::core::utils::Print::Line(anOutputStream) << "..." ;
    }

    if (aTable.getRowCount() > 3)
    {
        library::core::utils::Print::Line(anOutputStream) << formatLine(convertRowToStringArray(aTable[aTable.getRowCount() - 2])) ;
    }

    if (aTable.getRowCount() > 2)
    {
        library::core::utils::Print::Line(anOutputStream) << formatLine(convertRowToStringArray(aTable[aTable.getRowCount() - 1])) ;
    }

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Table::isEmpty                              ( ) const
{
    return rows_.isEmpty() ;
}

Size                            Table::getRowCount                          ( ) const
{
    return rows_.getSize() ;
}

Size                            Table::getColumnCount                       ( ) const
{
    return header_.getSize() ;
}

void                            Table::addRow                               (   const   Row&                        aRow                                        )
{

    while (aRow.getSize() > header_.getSize())
    {
        header_.add("") ;
    }

    rows_.add(aRow) ;

    rows_.accessLast().associateTable(this) ;

}

void                            Table::clear                                ( )
{
    rows_.clear() ;
}

Table::ConstIterator            Table::begin                                ( ) const
{
    return rows_.begin() ;
}

Table::ConstIterator            Table::end                                  ( ) const
{
    return rows_.end() ;
}

Table                           Table::Empty                                ( )
{
    return Table(Array<String>::Empty()) ;
}

Table                           Table::Load                                 (   const   File&                       aFile,
                                                                                const   Table::Format&              aFormat,
                                                                                        bool                        hasHeader                                   )
{

    if (!aFile.isDefined())
    {
        throw library::core::error::runtime::Undefined("File") ;
    }

    if (!aFile.exists())
    {
        throw library::core::error::RuntimeError("File [{}] does not exist.", aFile.toString()) ;
    }

    switch (aFormat)
    {

        case Table::Format::Undefined:
        {

            if (aFile.getExtension() == "csv")
            {
                return Table::LoadCsv(aFile, hasHeader) ;
            }
            else
            {
                throw library::core::error::RuntimeError("Cannot automatically detect format of table file [{}].", aFile.toString()) ;
            }

            break ;

        }

        case Table::Format::CSV:
            return Table::LoadCsv(aFile, hasHeader) ;

        default:
            throw library::core::error::runtime::Wrong("Format") ;
            break ;

    }

    return Table::Empty() ;

}

Table                           Table::LoadCsv                              (   const   File&                       aFile,
                                                                                        bool                        hasHeader                                   )
{

    using library::core::types::Integer ;
    using library::core::types::Real ;

    try
    {

        rapidcsv::Document document(aFile.getPath().toString(), (hasHeader ? rapidcsv::LabelParams(0, -1) : rapidcsv::LabelParams(-1, -1))) ;

        Array<String> header = Array<String>::Empty() ;

        if (hasHeader)
        {

            for (const auto& columnName : document.GetColumnNames())
            {
                header.add(columnName) ;
            }
            
        }

        Table table = Table(header) ;

        for (Size rowIndex = 0; rowIndex < document.GetRowCount(); ++rowIndex)
        {

            const auto documentRow = document.GetRow<std::string>(rowIndex) ;

            Array<Cell> cells = Array<Cell>::Empty() ;

            for (const auto& rowValue : documentRow)
            {

                Cell cell = Cell::Undefined() ;

                if (rowValue.empty())
                {
                    cell = Cell::Undefined() ;
                }
                else if (Integer::CanParse(rowValue))
                {
                    cell = Cell::Integer(Integer::Parse(rowValue)) ;
                }
                else if (Real::CanParse(rowValue))
                {
                    cell = Cell::Real(Real::Parse(rowValue)) ;
                }
                else
                {

                    if ((rowValue.length() > 2) && (rowValue.at(0) == '"') && (rowValue.at(rowValue.length() - 1) == '"'))
                    {
                        cell = Cell::String(rowValue.substr(1, rowValue.length() - 2)) ;
                    }
                    else
                    {
                        cell = Cell::String(rowValue) ;
                    }

                }

                cells.add(cell) ;

            }

            table.addRow(Row(cells)) ;

        }

        return table ;

        // std::vector<std::string> columnNames = doc.GetColumnNames();

        // io::CSVReader<3>        csvReader(aFile.getPath().toString()) ;

        // in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
        // std::string vendor; int size; double speed;
        // while(in.read_row(vendor, size, speed)){
        // // do stuff with the data
        // }

    }
    catch (const std::exception& anException)
    {
        throw library::core::error::RuntimeError("Cannot load table file [{}]: ({}).", aFile.toString(), anException.what()) ;
    }

    return Table::Empty() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////